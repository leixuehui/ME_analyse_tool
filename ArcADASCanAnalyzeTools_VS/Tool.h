#pragma once
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "global_header.h"

#include <string>
#include <Windows.h>
#include <vector>
#include <QImage>

std::string UTF8_To_string(const std::string & str);

std::string GBKToUTF8(const std::string& strGBK);

int listDevices(std::vector<std::string>& list);

QImage cvMatToQImage(const cv::Mat& mat);

bool writeToLocal(const QString&filePath, const ME_DeviceData& data);
