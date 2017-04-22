#include "widget.h"
#include "ui_widget.h"
#include "windows.h"

#include <QBuffer>
#include <QDataStream>
#include <QtWebEngine>
#include <QWebEngineSettings>

Widget::Widget(QWidget *parent) :QWidget(parent),ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->listWidget->setFrameStyle( QFrame::NoFrame );
    ui->listWidget->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->NotificationFrame->hide();

    SharedMemory.setKey("CyrillTS3AutoLinkOpenerThingy");
    ConfigMemory.setKey("CyrillTS3AutoLinkOpenerMessage");

    Settings = new SettingsManager();
    Settings->LoadFile();

    if (Settings->GetBool("LockWin"))
    {
        setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        SetWindowPos(reinterpret_cast<HWND>(this->winId()), HWND_DESKTOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
    else
        setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    if (Settings->GetBool("RememberPos"))
        this->move(Settings->GetVec("Pos").toPoint());

    if (Settings->GetBool("RememberSize"))
        this->setGeometry(this->pos().x(), this->pos().y(), Settings->GetSize("Size").width(), Settings->GetSize("Size").height());

    QWebEngineSettings::globalSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    ui->WebView->load(QUrl("https://upload.wikimedia.org/wikipedia/commons/c/ca/1x1.png"));

    Hotkey_ToggleAuto.setShortcut(QKeySequence(Settings->Get("HotkeyAuto")), true);
    connect(&Hotkey_ToggleAuto, SIGNAL(activated()), this, SLOT(HandleToggleAuto()));

    Hotkey_OpenLink.setShortcut(QKeySequence(Settings->Get("HotkeyOpen")), true);
    connect(&Hotkey_OpenLink, SIGNAL(activated()), this, SLOT(HandleOpenLink()));

    HotKey_CloseLink.setShortcut(QKeySequence(Settings->Get("HotkeyClose")), true);
    connect(&HotKey_CloseLink, SIGNAL(activated()), this, SLOT(HandleCloseLink()));

    Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()), this, SLOT(TimerPulse()));
    Timer->start(500);

    NotificationTimer = new QTimer(this);
    connect(NotificationTimer, SIGNAL(timeout()), this, SLOT(NotificationTimerPulse()));
    NotificationTimer->setSingleShot(true);

    if(!Settings->GetBool("FixedWin"))
        this->show();
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::GetURLFromString(QString& Text)
{
    QStringList TextSplit = Text.split("[URL]");

    if (TextSplit.length() >= 2)
    {
        QString URL = TextSplit[1].split("[/URL]")[0];

        QRegExp validURLRegex("^(http|https)://[a-z0-9]+([-.]{1}[a-z0-9]+)*.[a-z]{2,5}(([0-9]{1,5})?/?.*)$");
        QRegExpValidator validator(validURLRegex);
        int index = 0;
        if (validator.validate(URL, index) == QValidator::Acceptable)
        {
            Text = URL;
            return true;
        }
    }

    return false;
}
void Widget::UpdateURLList(QString URL)
{
    ui->listWidget->addItem(URL);

    if (ui->listWidget->count() == 1)
    {
        CurURLIndex = 0;
        ui->listWidget->item(0)->setSelected(true);
    }
    else if(ui->listWidget->count() >= Settings->GetInt("LinkHistory"))
    {
        delete ui->listWidget->item(0);
    }
}

void Widget::CheckURLMemory()
{
    if (!SharedMemory.attach())
    {
        //If an attempt of reading from the shared memory before data is written
        return;
    }

    QBuffer buffer;
    QDataStream in(&buffer);
    QString text;

    SharedMemory.lock();
    buffer.setData((char*)SharedMemory.constData(), SharedMemory.size());
    buffer.open(QBuffer::ReadWrite);
    in >> text;

    if (text == '\0')
    {
        SharedMemory.unlock();
        SharedMemory.detach();
        return;
    }

    memset((char*)SharedMemory.data(), '\0', SharedMemory.size());
    SharedMemory.unlock();
    // As this is the last process attached to the shared memory segment
    // the shared memory segment is released, destroying its contents
    SharedMemory.detach();

    if (GetURLFromString(text))
    {
        UpdateURLList(text);
        if(Settings->GetBool("AutoLoad"))
        {
            Load();
        }
    }
}
void Widget::CheckConfigMemory()
{
    if (!ConfigMemory.attach())
    {
        //If an attempt of reading from the shared memory before data is written
        return;
    }

    QBuffer buffer;
    QDataStream in(&buffer);
    QString text;

    ConfigMemory.lock();
    buffer.setData((char*)ConfigMemory.constData(), ConfigMemory.size());
    buffer.open(QBuffer::ReadWrite);
    in >> text;

    if (text == '\0')
    {
        ConfigMemory.unlock();
        ConfigMemory.detach();
        return;
    }
    else if (text == "OpenConfig")
    {
        SettingsForm.move(this->pos());
        SettingsForm.SetSettings(Settings);
        SettingsForm.show();
        this->hide();
    }

    memset((char*)ConfigMemory.data(), '\0', ConfigMemory.size());
    ConfigMemory.unlock();
    // As this is the last process attached to the shared memory segment
    // the shared memory segment is released, destroying its contents
    ConfigMemory.detach();
}

void Widget::Load()
{
    if (ui->listWidget->count() > 0)
    {
        this->show();

        ui->WebView->load(QUrl(ui->listWidget->item(CurURLIndex)->text()));
        delete ui->listWidget->item(CurURLIndex);
    }
}

void Widget::TimerPulse()
{
    CheckURLMemory();
    CheckConfigMemory();

    bool Save = false;

    if (Settings->GetBool("FixedWin"))
    {
        if (Settings->GetBool("RememberPos"))
            this->move(Settings->GetVec("Pos").toPoint());

        if (Settings->GetBool("RememberSize"))
        {
            auto Size = Settings->GetSize("Size");
            this->setGeometry(this->pos().x(), this->pos().y(), Size.width(), Size.height());
        }
    }
    else
    {
        if(Settings->GetBool("RememberPos") && this->pos() != Settings->GetVec("Pos").toPoint())
        {
            Settings->Set("Pos", this->pos());
            Save = true;
        }

        if(Settings->GetBool("RememberSize") && this->size() != Settings->GetSize("Size"))
        {
            Settings->Set("Size", this->size());
            Save = true;
        }
    }

    if (Save)
        Settings->SaveFile();
}

void Widget::NotificationTimerPulse()
{
    ui->NotificationFrame->hide();
}

void Widget::HandleToggleAuto()
{
    Settings->Set("AutoLoad", !Settings->GetBool("AutoLoad"));
    ui->NotificationFrame->show();
    NotificationTimer->start(2000);

    QString TF = Settings->GetBool("AutoLoad") ? "true" : "false";
    ui->NotificationLabel->setText("Auto Load Enabled: " + TF);
}
void Widget::HandleDeleteLink()
{
    if (ui->listWidget->count() > 0)
    {
        delete ui->listWidget->item(CurURLIndex);
    }
}
void Widget::HandleOpenLink()
{
    Load();
}
void Widget::HandleCloseLink()
{
    ui->WebView->load(QUrl("https://upload.wikimedia.org/wikipedia/commons/c/ca/1x1.png"));
    if(Settings->GetBool("FixedWin"))
        this->hide();
}

void Widget::resizeEvent(QResizeEvent *e)
{
    ui->WebView->setFixedSize(e->size());
    ui->listWidget->setFixedSize(e->size());

    int y = e->size().height() - ui->NotificationFrame->geometry().height();
    ui->NotificationFrame->setGeometry(0, y, e->size().width(), e->size().height());
}
void Widget::closeEvent(QCloseEvent *)
{
    SettingsForm.close();
    this->close();
}
