#include "canparser.h"
#include "Widget/MyLabel.h"

CanParser::CanParser(QObject *parent) : QObject(parent)
{

}

CanParser::~CanParser()
{

}

void CanParser::showCanFrameInfo(VCI_CAN_OBJ *obj)
{
	QString info("");
	QTextStream stream(&info);
	stream << "0x" << QString::number(obj->ID, 16);
	stream << ", ";
	stream << obj->ExternFlag;
	stream << ", ";
	stream << obj->RemoteFlag;
	stream << ", ";
	stream << obj->SendType;
	stream << ", ";
	stream << obj->DataLen;
	stream << ",";
	for (unsigned char j = 0; j < obj->DataLen; j++)
	{
		stream << " " << QString("%1").arg(obj->Data[j], 2, 16, QLatin1Char('0'));
	}

	qInfo() << stream.readAll();
}