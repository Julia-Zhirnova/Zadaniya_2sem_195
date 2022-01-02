#include <stdio.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <string>
#include <cstring>

using namespace cv;
using namespace std;

void my_mouse_callback(int event, int x, int y, int flags, void* param);
int reading(char* Filename, char* imagename, double wl, double hl, double wr, double hr);
void file();

int main(int argc, char** argv) {
	// устанвливаем русскую локаль для консоли
	setlocale(LC_ALL, "Russian");
	//file();
	
	char* imagename = "Dzerzhinsky.png";
	char* traectory_file = "coordinat.txt";
	double wl = 55.639799;
	double hl = 37.828428;
	double wr = 55.622020;
	double hr = 37.873735;
	reading(traectory_file, imagename, wl, hl, wr, hr);
		
	/*Mat image = imread("Dzerzhinsky.png");
	
	namedWindow("modernGoogle");
	setMouseCallback("modernGoogle", my_mouse_callback, &image);

	while(true){
		imshow("modernGoogle",image);
		waitKey(30);}
	return(0);*/
}

void file()
{
	ofstream file;
	file.open("test.txt", ios_base::app);
	unsigned long milliseconds_since_epoch = chrono::system_clock::now().time_since_epoch() / chrono::milliseconds(1);
	file << milliseconds_since_epoch << endl;
	file.close();
	
}

void my_mouse_callback(int event, int x, int y, int flags, void* param)
{
 if (event == EVENT_LBUTTONDOWN) 
  {
	Mat* pImage = (Mat*)param;
	Mat image = *pImage;
	circle(image, Point(x, y), 5, Scalar(255, 0, 0), FILLED, 8, 0);
	ofstream file;
	file.open("coordinat.txt", ios_base::app);
	unsigned long milliseconds_since_epoch = chrono::system_clock::now().time_since_epoch() / chrono::milliseconds(1);
	file << milliseconds_since_epoch << " " << x << " " << y << endl;
	file.close();
  }
}

int reading(char* Filename, char* imagename, double wl, double hl, double wr, double hr)
{
	const char* File = Filename;
	int x, y, xm, ym;
	unsigned long t, tt;
	long double shirota, dolgota;

	ifstream f(File);
	if (!(f.is_open()))  cout << "Ошибка открытия файла" << File;
	else
	{
		Mat img = imread(imagename);
		cout << "Размер изображения: " << endl;
		cout << "Ширина: " << img.size().width << endl;
		cout << "Высота: " << img.size().height << endl;
		//вычисляем коэффициент масштабирования
		long double koef_mashtabW, koef_mashtabH;
		koef_mashtabW = (wl - wr) / img.size().width;
		koef_mashtabH = (hr - hl) / img.size().height;
		//cout << koef_mashtabW << koef_mashtabH << endl;

		f >> t >> x >> y;

		cout << "Ваш путь пролегает по следующему  маршруту: " << endl;
		while (!f.eof())
		{
			f >> tt >> xm >> ym;

			//cout << "Метка времени: " << t << " x: " << x << " y: " << y << endl;
			shirota = koef_mashtabW * (img.size().width - x) + wr;
			dolgota = koef_mashtabH * (img.size().height - y) + hl;
			cout << "Метка времени: " << t << " широта: " << shirota << " долгота: " << dolgota << endl;

			circle(img, Point(x, y), 5, Scalar(0, 0, 255), FILLED, 8, 0);
			x = xm;
			y = ym;
			imshow("route", img);
			waitKey(tt - t);
			t = tt;
		}
	}

	f.close();
	cout << endl;
	return 0;
}
