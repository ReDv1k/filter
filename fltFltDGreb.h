#ifndef HG_C9A006B0_EDBE_4710_9948_FA745523A56F
#define HG_C9A006B0_EDBE_4710_9948_FA745523A56F

#ifndef HG_DVL_FILTER_fltFltDGreb
#define HG_DVL_FILTER_fltFltDGreb

#include <QObject>
#include <QtConcurrent/QtConcurrentRun>
#include <QFuture>

#include <filter_interfaces.h>

class fltFltDGreb : public QObject, public FilterInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ru.DiViLine.DiViLab2.ESKIZ-V.FilterInterface" FILE "fltFltDGreb.json")
    Q_INTERFACES(FilterInterface)

public:
    void getFilterParameters(DVL_FilterParams& params) override;
    int	 init(DVL_FilterArguments_In &in_args, DVL_FilterParams& params) override;
    int	 process(DVL_FilterArguments_In& in_args, DVL_FilterArguments_Out& out_args) override;
    void clean() override;

private:
    // TODO: Здесь определять свои переменные, константы, функции.
    qint32	width = 0;	// Ширина кадра.
    qint32	height = 0;	// Высота кадра.

    // Коэффициент понижения яркости (в 2 раза).
    qint32	K_br = 2;

    // Значение числового параметра
    double number_parametr = 1.0;

    // Значение строкового параметра
    QString string_parametr = "Hello params dialog";

    // Значение параметра включения/отключения чего-либо
    bool checkBox = true;

    // Значение параметра выбора значения из диапазона
    // Для работы с выбранным значением "слайдера"
    qint32 slider_value = 2;

    // Значение параметра выбора одного из нескольких
    QString comboBox = "One;Two;Three;Four";

    // Значение параметра Color по умолчанию
    quint32 color = 0x892ac0;


    qint32 curve_id = 0;
    qint32 graph_id = 0;
    qint32 image_id = 0;

    quint8*	tempImageBuff = nullptr;



    // Функции вашего фильтра
    void inverseImage(const quint8 *inp, quint8 *out);
    void imageBrightDivide(const quint8 *inp, quint8 *out, qint32 divider);

};

#endif // HG_DVL_FILTER_fltFltDGreb

#endif // HG_C9A006B0_EDBE_4710_9948_FA745523A56F
