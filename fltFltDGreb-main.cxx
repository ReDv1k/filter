#include <QDebug>

#include <fltFltDGreb.h>





void fltFltDGreb::getFilterParameters(DVL_FilterParams& params)
{
	params.setFilterId(4002); // ID фильтра, у каждого фильтра свой ID! 	// divilab	- 4000 и более
	params.setFilterName("Filter fltFltDGreb");
	params.setFilterDescription("Demonstration of processed images, graphs, notes");

	params.setRequiredData("rgb24"); //запрашмваемые входные данные

	/* Включение параметров фильтра разных типов
	 *	Параметр по умолчанию:
	 *	params.newParam("Название параметра фильтра", значение по умолчанию);
	 *Параметры разных типов:
	 *	Все функции инициализации новых параметров имеют несколько обязательный параметров
	 *  - Название параметра фильтра (QString)
	 *  - Значение параметра по умолчанию (тип зависит от типа параметра):
	 *		"Number" - числовой параметр, тип данных double;
	 *		"String" - строковый параметр, тип данных QString;
	 *		"CheckBox" - параметр выбора (галочка) включения/выключения, тип данных - bool (true/false);
	 *		"Slider" - параметр бегунок, для настройки переменной в диапазоне значений, тип данных:
	 *					double min - минимум шкалы слайдера;
	 *					double max - максимум шкалы слайдера;
	 *					double value - значение слайдера по умолчани, то которое будет использоваться;
	 *					double step - шаг изменения значения слайдера;
	 *		"ComboBox" - выпадающий список, позволяющий выбирать один из нескольких значений, тип -
	 *				QString{"Значение_1;Значение_2;...;Значение_Х" };
	 *		"Color" - параметр добавляет возможность выбора цвета для дальнейшего использования, тип -
	 *				quint32 0xFFFFFF, где первые 2 знака (после x) значение красного (0-9, A-F)
	 *									  вторые 2 знака (после x) значение зеленого (0-9, A-F)
	 *									  третьи 2 знака (после x) значение зеленого (0-9, A-F)
	 *  и один со значением по умолчанию:
	 *	- описание параметра - может отсутствовать.
	 *
	 * Общий вид:
	 *
	 *	params.newParamType("Название параметра", значение по умолчанию, "Описание параметра);
	 *
	 * Инициализация параметров разных типо
	 *
	 *		params.newParamNumber("Number param", 1.0,);
	 *
	 *		params.newParamString("String param", "String", "Строковый параметр");
	 *
	 *		params.newParamCheckBox("CheckBox", true, "Параметр включения/отключения чего-либо");
	 *
	 *		params.newParamSlider("Название параметра",	min,	max,	value,	step,	"Описание параметра);
	 *		params.newParamSlider("Slider 1",			1,		10,		2,		1,		"Параметр выбора значения из диапазона");
	 *
	 *		params.newParamComboBox("Название параметра",	"Перечисление значений",	default_value, "Описание параметра);
	 *		params.newParamComboBox("ComboBox Param",		"One;Two;Three;Four",		"Three,			"Параметр выбора одного из нескольких");
	 *			ВАЖНО: Для правильной работы параметра необходимо:	либо перечислять элементы без пробелов,
	 *																либо учитывать пробелы при работе с параметром.
	 *			ВАЖНО: Обязательно между элементами должен быть знак ";"
	 *
	 *		params.newParamColor("Название параметра",	Значение цвета в виде HEX,	"Параметр выбора цвета" );
	 *		params.newParamColor("ColorDialog Param",	0x892ac0,					"Параметр выбора цвета" );
	 * */

	params.newParamNumber("Number param", 1.0, "Числовой параметр" );

	params.newParamString("String param", "String", "Строковый параметр");

	params.newParamCheckBox("CheckBox", true, "Параметр включения/отключения чего-либо");

	params.newParamSlider("Slider", 1, 10, 3, 1, "Параметр выбора значения из диапазона");

	params.newParamComboBox("ComboBox Param", "One;Two;Three;Four", "Параметр выбора одного из нескольких");
	
	params.newParamColor("ColorDialog Param", 0x892ac0, "Параметр выбора цвета" );
}

int fltFltDGreb::init(DVL_FilterArguments_In& in_args, DVL_FilterParams& params)
{
		// outDbgMsg(__FUNCTION__); // Пример отладочного сообщения с именем функции.
	// TODO: 1. Инициализировать переменные, выделить память, и пр.
	// TODO: 2. Запросить память для графиков таймлайн, графиков на кадр
	//			и изображений с указанными ID и названиями.

	// EXAMPLE:
	// Step 1.
	width = in_args.frame_width;
	height = in_args.frame_height;

	//! Получить значение числового параметра
	number_parametr = params.getParamNumber("Number param");
	K_br = number_parametr;

    //! Получить значение строкового параметра
	string_parametr = params.getParamString("String param");

	//! Получить значение параметра включения/выключения
	checkBox = params.getParamCheckBox("CheckBox");
	// Чаще всего будет использоваться в условном операторе
	// if(checkBox){...}
	// else {...}

	//! Получить значение параметра выбора значения из диапозона
	slider_value = params.getParamSlider("Slider");

	//! Получить значение параметра выбора одного из нескольких
	comboBox = params.getParamComboBox("ComboBox Param");

	//! Получить значение параметра выбора цвета
	color = params.getParamColor("ColorDialog Param");

	
	// Примеры отладочных сообщений с параметрами:
//	QString dbg_msg = QString("Ширина кадра = %1, высота кадра = %2").arg(width).arg(height);
//	outDbgMsg(dbg_msg);
//	outDbgMsg("K_br = " + QString::number(K_br) + " (brightness devider)");

	tempImageBuff = new quint8 [width * height * 3]; // (R, G, B)

	// Step 2.
	// (ID, name) 1-го графика на таймлайн
	in_args.newCurve(curve_id++, "Timeline graph 1");
	in_args.newCurve(curve_id++, "Timeline graph 2");
	// (ID, name, размер) 1-го графика кадра.
	in_args.newGraph(graph_id++, "Frame graph 1", 2 * width); // Удвоение для хранения пар (X,Y)
	in_args.newGraph(graph_id++, "Frame graph 2", 2 * width);
	// (ID, name, ширина кадра, высота кадра) 1-го набора обработанных кадров.
	in_args.newImage(image_id++, "Frame image 1", width, height);
	in_args.newImage(image_id++, "Frame image 2", width, height);
	in_args.newImage(image_id++, "Frame image 3", width, height);
	return 0; // 0, если нет ошибок.
}

void fltFltDGreb::clean()
{
	// TODO: Освободить выделенную память.
	delete[] tempImageBuff;
}

int fltFltDGreb::process(DVL_FilterArguments_In& in_args, DVL_FilterArguments_Out& out_args)
{
	// TODO: 1. Получить из in_args входные данные и значения параметров фильтра
	//			(которые задал пользователь).
	// TODO: 2. Получить указатели на память для изображений и графиков
	// TODO: 3. Обработать данные.
	// TODO: 4. Добавить результаты обработки в out_args.

	// EXAMPLE:
	const quint8* inp_rgb24 = in_args.getInputBuffer("rgb24");
	if (!inp_rgb24)
		return Error | NotEnoughInputData;

	curve_id = graph_id = image_id = 0;
	qint32 current_frame_number = in_args.frame_num;
	quint8 *out_image0 = out_args.getImageBuffer(image_id++);
	quint8 *out_image1 = out_args.getImageBuffer(image_id++);
	quint8 *out_image2 = out_args.getImageBuffer(image_id++);
	double *out_graph0 = out_args.getGraphBuffer(graph_id++);
	double *out_graph1 = out_args.getGraphBuffer(graph_id++);
	// Можно получить указатели другим способом:
//	quint8 *out_image0 = out_args.getImageBuffer("My 1 frame image");
//	quint8 *out_image1 = out_args.getImageBuffer("My 2 frame image");
//	double *out_graph0 = out_args.getGraphBuffer("My 1 frame graph");
//	double *out_graph1 = out_args.getGraphBuffer("My 2 frame graph");
	if(!out_image0 || !out_image1 || !out_image2 || !out_graph0 || !out_graph1)
		return Error | OutputBufferError;

	// Добавить заключение к каждому нечетному кадру.
	if (current_frame_number & 1)
		out_args.putFrameConclusion(QString("Нечетный кадр, номер кадра \"%1\"<BR>").arg(current_frame_number));


    imageBrightDivide(inp_rgb24, out_image1, K_br); // Уменьшаем яркость в K_br раз.
    // запускаем функции обработки в разных потоках
   QFuture future = QtConcurrent::run(this, &fltFltDGreb::inverseImage(inp_rgb24, out_image0),  &fltFltDGreb::imageBrightDivide(inp_rgb24, out_image2, slider_value));
    //QtConcurrent::run(QThreadPool::globalInstance(), inverseImage(inp_rgb24, out_image0), imageBrightDivide(inp_rgb24, out_image2, slider_value));
   // QtConcurrent::run(inverseImage(inp_rgb24, out_image0), imageBrightDivide(inp_rgb24, out_image2, slider_value));
    //inverseImage(inp_rgb24, out_image0);// Инвертируем значения RGB компонент.
    //imageBrightDivide(inp_rgb24, out_image1, K_br);// Уменьшаем яркость в K_br раз.
    //imageBrightDivide(inp_rgb24, out_image2, slider_value);// Уменьшаем яркость в выбранное (с использованием слайдера) колличество раз.

	// Сохранить значение точки для текущего кадра на 1 графике таймлайн, если
	// в настройках фильтра стоит "галочка":
	// if(checkBox)
	// out_args.putFileCurvePoint(curve_id++, current_frame_number);
	// или:
	if(checkBox)
	out_args.putFileCurvePoint("Timeline graph 1", current_frame_number);

	// Сохранить значение точки для текущего кадра на 2 графике таймлайн
	// Кривая яркости (её изменение с течением времени),
	// центральный пиксель кадра, R-компонента.
	// out_args.putFileCurvePoint(curve_id++, inp_rgb24[3 * width * height / 2]);
	// или:
	out_args.putFileCurvePoint("Timeline graph 2", inp_rgb24[3 * width * height / 2]);

	// Сохранить данные покадровых графиков:
	for (auto i = 0; i < width; ++i)
	{
	// График яркости R-пикселей срединной строки в области, выбранной на кадре.
	   out_graph0[i * 2 + 0] = i;
	   out_graph0[i * 2 + 1] = inp_rgb24[3 * (width * height / 2 + i)];
	// Такой же график, но после обработки (понижения яркости).
	   out_graph1[i * 2 + 0] = i;
	   out_graph1[i * 2 + 1] = out_image1[3 * (width * height / 2 + i)];
	}

	// Добавить запись в общее заключение ко всему файлу.
	if(current_frame_number == 0)
	{
		out_args.putFileConclusion(QString("Параметр \"%1\" имеет значение %2 <BR>").arg("Number param").arg(number_parametr));
		out_args.putFileConclusion(QString("Параметр \"%1\" имеет значение \"%2\" <BR>").arg("String parametr").arg(string_parametr));
		out_args.putFileConclusion(QString("Параметр \"%1\" имеет значение %2 <BR>").arg("CheckBox").arg(checkBox ? "\"TRUE\"" : "\"FALSE\""));
		out_args.putFileConclusion(QString("Параметр \"%1\" имеет значение \"%2\" <BR>").arg("Slider").arg(slider_value));
		out_args.putFileConclusion(QString("Параметр \"%1\" имеет значение \"%2\" <BR>").arg("ComboBox Param").arg(comboBox));
		out_args.putFileConclusion(QString("Параметр \"%1\" имеет значение:  %2 <BR>").arg("ColorDialog Param").arg(QString::number(color, 16)));
	}
	return Success;
}
