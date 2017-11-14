#include "lipa.h"
#include <iostream>
#include <string>
using namespace std;

//LipaLib - Learning Image Processing Autonomic Library


void thresholding(Image3CH& colourimg, Image1CH& threshimg, double lowerthreshred, double upperthreshred,
	double lowerthreshgreen, double upperthreshgreen, double lowerthreshblue, double upperthreshblue)
{
	for (int i = 0; i < colourimg.width(); i++){
		for (int j = 0; j < colourimg.height(); j++)
		{
			if (colourimg(i, j).Red() > lowerthreshred && colourimg(i, j).Red() < upperthreshred){
				if (colourimg(i, j).Green() > lowerthreshgreen && colourimg(i, j).Green() < upperthreshgreen){
					if (colourimg(i, j).Blue() > lowerthreshblue && colourimg(i, j).Blue() < upperthreshblue)
						threshimg(i, j).Intensity() = 1;
				}
			}
			else threshimg(i, j).Intensity() = 0;
		}
	}
}


void erosion(Image1CH& binaryimg, Image1CH& treshimg){
	for (int i = 1; i < binaryimg.width() - 1; i++){
		for (int j = 1; j < binaryimg.height() - 1; j++){
			if (treshimg(i, j).Intensity() == 1){
				if (treshimg(i - 1, j - 1).Intensity() == 0)
					binaryimg(i, j).Intensity() = 0;
				else if (treshimg(i - 1, j).Intensity() == 0)
					binaryimg(i, j).Intensity() = 0;
				else if (treshimg(i - 1, j + 1).Intensity() == 0)
					binaryimg(i, j).Intensity() = 0;
				else if (treshimg(i, j - 1).Intensity() == 0)
					binaryimg(i, j).Intensity() = 0;
				else if (treshimg(i, j + 1).Intensity() == 0)
					binaryimg(i, j).Intensity() = 0;
				else if (treshimg(i + 1, j - 1).Intensity() == 0)
					binaryimg(i, j).Intensity() = 0;
				else if (treshimg(i + 1, j).Intensity() == 0)
					binaryimg(i, j).Intensity() = 0;
				else if (treshimg(i + 1, j + 1).Intensity() == 0)
					binaryimg(i, j).Intensity() = 0;
				else binaryimg(i, j).Intensity() = 1;
			}
		}
	}
}

void redspoterasure(Image1CH& processedimage, Image3CH& comparisonimage, double rtgthresh1, double rtgthresh2){
	{
		for (int i = 0; i < processedimage.width(); i++){
			for (int j = 0; j < processedimage.height(); j++)
			{
				if (processedimage(i, j).Intensity() == 1){
					if (comparisonimage(i, j).Red() / comparisonimage(i, j).Green()<rtgthresh1 || comparisonimage(i, j).Red() / comparisonimage(i, j).Green()>rtgthresh2){
						processedimage(i, j).Intensity() = 0;
					}
				}
			}
		}
	}
}

void bluespoterasure(Image1CH& processedimage, Image3CH& comparisonimage, double btgthresh1, double btgthresh2){
	{
		for (int i = 0; i < processedimage.width(); i++){
			for (int j = 0; j < processedimage.height(); j++)
			{
				if (processedimage(i, j).Intensity() == 1) {
					if (comparisonimage(i, j).Blue() / comparisonimage(i, j).Green()<btgthresh1 || comparisonimage(i, j).Blue() / comparisonimage(i, j).Green()>btgthresh2){
						processedimage(i, j).Intensity() = 0;
					}
				}
			}
		}
	}
}

void greenspoterasure(Image1CH& processedimage, Image3CH& comparisonimage, double rtbthresh1, double rtbthresh2){
	for (int i = 0; i < processedimage.width(); i++){
		for (int j = 0; j < processedimage.height(); j++)
		{
			if (processedimage(i, j).Intensity() == 1){
				if (comparisonimage(i, j).Red() / comparisonimage(i, j).Blue() < rtbthresh1 || comparisonimage(i, j).Red() / comparisonimage(i, j).Blue() > rtbthresh2){
					processedimage(i, j).Intensity() = 0;
				}
			}
		}
	}
}

void dilation(Image1CH& binaryimg, Image1CH& treshimg){
	for (int i = 1; i < binaryimg.width() - 1; i++){
		for (int j = 1; j < binaryimg.height() - 1; j++){
			if (treshimg(i - 1, j - 1).Intensity() == 1)
				binaryimg(i, j).Intensity() = 1;
			else if (treshimg(i - 1, j).Intensity() == 1)
				binaryimg(i, j).Intensity() = 1;
			else if (treshimg(i - 1, j + 1).Intensity() == 1)
				binaryimg(i, j).Intensity() = 1;
			else if (treshimg(i, j - 1).Intensity() == 1)
				binaryimg(i, j).Intensity() = 1;
			else if (treshimg(i, j + 1).Intensity() == 1)
				binaryimg(i, j).Intensity() = 1;
			else if (treshimg(i + 1, j - 1).Intensity() == 1)
				binaryimg(i, j).Intensity() = 1;
			else if (treshimg(i + 1, j).Intensity() == 1)
				binaryimg(i, j).Intensity() = 1;
			else if (treshimg(i + 1, j + 1).Intensity() == 1)
				binaryimg(i, j).Intensity() = 1;
			else binaryimg(i, j).Intensity() = 0;
		}
	}
}
int minimum_nonzero(int input_array[][3])
{
	int smallest = 9999999;
	for (int i = 0; i < 3; i++)

	{
		for (int j = 0; j < 3; j++){
			if (input_array[i][j] != 0){
				if (input_array[i][j] < smallest)
					smallest = input_array[i][j];
			}
		}
	}

	return smallest;
}

int present_or_not(int input_array[], int to_check){
	int truth = 1;
	for (int i = 0; i < 26; i++){
		if (input_array[i] == to_check){
			truth = 2;
			break;
		}
	}
	return truth;

}

int surface_area(int min_l, int max_l, int min_h, int max_h, int **a_o_l){
	int counter = 0;
	for (int i = min_l; i < max_l + 1; i++){
		for (int j = min_h; j < max_h + 1; j++){
			if (a_o_l[i][j] != 0)
			{
				counter = counter + 1;
			}
		}
	}
	return counter;
}

int* arrange(int array_to_sort[], int euler[], double prop[]){
	int array_to_write[26];
	int new_array[26];

	for (int i = 0; i < 26; i++)
	{
		array_to_write[i] = 99999999;
		new_array[i] = array_to_sort[i];

	}
	char letters[26] = { 'd', 'o', 'k', 'w', 'i', 'ó', 'c', 'r', 'a', 'g', 'a', 't', 'w', 'o', 'y', 'r', 'y', 'a', 'g', 'b', 'u', 'r', 'z', 'o', 'z', 'n' };
	char letters_to_print[26];
	int euler_n[26];
	int counter;
	double prop_prop[26];
	for (int i = 0; i < 26; i++){
		for (int j = 0; j < 26; j++){

			if (array_to_write[i]>new_array[j]){
				array_to_write[i] = new_array[j];

				counter = j;
				letters_to_print[i] = letters[j];
			}
		}
		prop_prop[i] = prop[counter];
		euler_n[i] = euler[counter];
		new_array[counter] = 999999;
	}
	return array_to_write;
}

int euler(int min_l, int max_l, int min_h, int max_h, int **input_array)
{
	int  Q1 = 0, Q3 = 0, QD = 0, E = 0;

	for (int row = min_l - 15; row < max_l + 15; row++)
	{
		for (int column = min_h - 15; column < max_h + 15; column++)
		{


			if (
				((input_array[row][column] == 0) && (input_array[row][column + 1] > 0) && (input_array[row + 1][column] > 0) && (input_array[row + 1][column + 1] > 0))
				|| ((input_array[row][column] > 0) && (input_array[row][column + 1] == 0) && (input_array[row + 1][column] > 0) && (input_array[row + 1][column + 1] > 0))
				|| ((input_array[row][column] > 0) && (input_array[row][column + 1] > 0) && (input_array[row + 1][column] == 0) && (input_array[row + 1][column + 1] > 0))
				|| ((input_array[row][column] > 0) && (input_array[row][column + 1] > 0) && (input_array[row + 1][column] > 0) && (input_array[row + 1][column + 1] == 0))
				)
			{
				Q3++;

			}

			if (
				((input_array[row][column] > 0) && (input_array[row][column + 1] == 0) && (input_array[row + 1][column] == 0) && (input_array[row + 1][column + 1] == 0))
				|| ((input_array[row][column] == 0) && (input_array[row][column + 1] > 0) && (input_array[row + 1][column] == 0) && (input_array[row + 1][column + 1] == 0))
				|| ((input_array[row][column] == 0) && (input_array[row][column + 1] == 0) && (input_array[row + 1][column] > 0) && (input_array[row + 1][column + 1] == 0))
				|| ((input_array[row][column] == 0) && (input_array[row][column + 1] == 0) && (input_array[row + 1][column] == 0) && (input_array[row + 1][column + 1] > 0))
				)
			{
				Q1++;


			}


			if (
				((input_array[row][column] > 0) && (input_array[row][column + 1] == 0) && (input_array[row + 1][column] == 0) && (input_array[row + 1][column + 1] > 0))
				|| ((input_array[row][column] == 0) && (input_array[row][column + 1] > 0) && (input_array[row + 1][column] > 0) && (input_array[row + 1][column + 1] == 0))
				)
			{
				QD++;

			}
		}
	}

	E = 0.25*(Q1 - Q3 - (2 * QD));
	return E;

}

double proportion_of_area(int min_l, int max_l, int min_h, int max_h, int **a_o_l){
	double black_counter = 0.0;
	double white_counter = 0.0;
	double a_proportion;
	for (int i = min_l; i < max_l + 1; i++){
		for (int j = min_h; j < max_h + 1; j++){
			if (a_o_l[i][j] == 0)
			{

				black_counter = black_counter + 1.0;
			}
			else
				white_counter = white_counter + 1.0;
		}
	}

	a_proportion = white_counter / (black_counter + white_counter);
	return a_proportion;
}

char assign_letters(int size_num, double proportion_num, int euler_num, int seg_num){
	char letter;
	//char letters[26] = { 'd', 'o', 'k', 'w', 'i', 'ó', 'c', 'r', 'a', 'g', 'a', 't', 'w', 'o', 'y', 'r', 'y', 'a', 'g', 'b', 'u', 'r', 'z', 'o', 'z', 'n' };
	for (int i = 0; i < 26; i++){
		///std::cout << size[i] << "\t" << proportion[i] << "\t" << euler[i] << "\n";
	}
	if (euler_num == -1){
		letter = 'b';
	}
	else if (euler_num == 0){
		if (size_num < 1650)
			letter = 'a';
		else{
			if (proportion_num < 0.48)
				letter = 'ó';
			else if (proportion_num > 0.5 && proportion_num < 0.52)
				letter = 'o';
			else if (proportion_num > 0.7)
				letter = 'r';
			else {
				if (size_num < 2000)
					letter = 'd';
				else
					letter = 'n';
			}
		}
	}
	else{
		if (size_num < 1000)
			letter = 'i';
		else if (size_num > 1000 && size_num < 1100)
			letter = 't';
		else if (size_num > 1300 && size_num < 1400)
			letter = 'c';
		else if (size_num > 1450 && size_num < 1500)
			letter = 'y';
		//else if (size_num > 1650 && size_num < 1700)
		//	
		else if (size_num > 1750 && size_num < 1800)
			letter = 'u';
		else if (size_num > 2050 && size_num < 2100)
			letter = 'k';
		else if (size_num >2500)
			letter = 'w';
		else
		{
			if (proportion_num < 0.555)
				letter = 'g';
			else
				letter = 'z';

		}
			

	}

	return letter;
}

//int highest_vertical_letter_that_begins_a_word()

// =================
//=============================//

int main()
{	
	// Zaladowanie obrazu oryginalnego
	Image3CH ColourImage(1600, 1200);

	ColourImage.LoadImage("img\\img.jpg", LPL_LOAD_ORIGINAL);

	ColourImage.ShowImage("res");

	// Progowanie

	Image1CH ThresholdImage(1600, 1200);
	thresholding(ColourImage, ThresholdImage, 0.45, 0.82, 0.45, 0.72, 0.32, 0.61);
	//ThresholdImage.ShowImage("res");


	// Oblicz stosunki intensywnoœci kolorów

	// Jasny ¿ó³ty kwadracik
	//double sumred = 0;
	//double sumgreen = 0;
	//double sumblue = 0;
	//double count = 0;
	//double totalintensity = 0;

	//for (int i = 915; i < 1033; i++)
	//for (int j = 904; j < 1006; j++){
	//	if (ThresholdImage(i, j).Intensity() == 1){
	//		sumred = sumred + ColourImage(i, j).Red();
	//		sumgreen = sumgreen + ColourImage(i, j).Green();
	//		sumblue = sumblue + ColourImage(i, j).Blue();
	//		count = count + 1;
	//	}
	//}

	//totalintensity = (sumred + sumgreen + sumblue) / (3 * count);
	//cout << "Ca³kowita intensywnoœæ jasnego kwadracika wynosi: " << totalintensity << endl;

	//double ratiortg_zolty_jasny = sumred / sumgreen;
	//double ratiortb_zolty_jasny = sumred / sumblue;
	//double ratiobtg_zolty_jasny = sumblue / sumgreen;

	//// Ciemny ¿ó³ty kwadracik
	//sumred = 0;
	//sumgreen = 0;
	//sumblue = 0;
	//count = 0;

	//for (int i = 778; i < 881; i++)
	//for (int j = 171; j < 248; j++){
	//	if (ThresholdImage(i, j).Intensity() == 1){
	//		sumred = sumred + ColourImage(i, j).Red();
	//		sumgreen = sumgreen + ColourImage(i, j).Green();
	//		sumblue = sumblue + ColourImage(i, j).Blue();
	//		count = count + 1;
	//	}
	//}

	//totalintensity = (sumred + sumgreen + sumblue) / (3 * count);
	//cout << "Ca³kowita intensywnoœæ ciemnego kwadracika wynosi: " << totalintensity << endl;

	//double ratiortg_zolty_ciemny = sumred / sumgreen;
	//double ratiortb_zolty_ciemny = sumred / sumblue;
	//double ratiobtg_zolty_ciemny = sumblue / sumgreen;

	//// Czerwony kwadracik 1
	//sumred = 0;
	//sumgreen = 0;
	//sumblue = 0;
	//count = 0;

	//for (int i = 344; i < 451; i++)
	//for (int j = 943; j < 1039; j++){
	//	if (ThresholdImage(i, j).Intensity() == 1){
	//		sumred = sumred + ColourImage(i, j).Red();
	//		sumgreen = sumgreen + ColourImage(i, j).Green();
	//		sumblue = sumblue + ColourImage(i, j).Blue();
	//		count = count + 1;
	//	}
	//}

	//double ratiortg_czerwony1 = sumred / sumgreen;
	//double ratiortb_czerwony1 = sumred / sumblue;
	//double ratiobtg_czerwony1 = sumblue / sumgreen;

	//// Czerwony kwadracik 2 

	//sumred = 0;
	//sumgreen = 0;
	//sumblue = 0;
	//count = 0;

	//for (int i = 1202; i < 1322; i++)
	//for (int j = 937; j < 1031; j++){
	//	if (ThresholdImage(i, j).Intensity() == 1){
	//		sumred = sumred + ColourImage(i, j).Red();
	//		sumgreen = sumgreen + ColourImage(i, j).Green();
	//		sumblue = sumblue + ColourImage(i, j).Blue();
	//		count = count + 1;
	//	}
	//}

	//double ratiortg_czerwony2 = sumred / sumgreen;
	//double ratiortb_czerwony2 = sumred / sumblue;
	//double ratiobtg_czerwony2 = sumblue / sumgreen;
	//
	//// Porównanie stosunków jasnoœci kolorów

	//cout << "Stosunek czerwonego do zielonego: " << ratiortg_zolty_jasny << " jasny ¿ó³ty, " << ratiortg_zolty_ciemny << " ciemny ¿ó³ty, " << ratiortg_czerwony1 << " czerwony 1, " << ratiortg_czerwony2 << " czerwony 2" << endl;
	//cout << "Stosunek czerwonego do niebieskiego: " << ratiortb_zolty_jasny << " jasny ¿ó³ty, " << ratiortb_zolty_ciemny << " ciemny ¿ó³ty, " << ratiortb_czerwony1 << " czerwony 1, " << ratiortb_czerwony2 << " czerwony 2" << endl;
	//cout << "Stosunek niebieskiego do zielonego: " << ratiobtg_zolty_jasny << " jasny ¿ó³ty, " << ratiobtg_zolty_ciemny << " ciemny ¿ó³ty, " << ratiobtg_czerwony1 << " czerwony 1, " << ratiobtg_czerwony2 << " czerwony 2" << endl;

	//
	// Usuniecie pikseli o niewlasciwym stosunku czerwonego do zielonego
	redspoterasure(ThresholdImage, ColourImage, 0.97, 1.15);
	//ThresholdImage.ShowImage("res");

	// Usuniecie pikseli o niewlasciwym stosunku niebieskiego do zielonego
	bluespoterasure(ThresholdImage, ColourImage, 0.66, 0.87);
	//ThresholdImage.ShowImage("res");

	// Usuniecie pikseli o niewlasciwym stosunku czerwonego do niebieskiego
	greenspoterasure(ThresholdImage, ColourImage, 1.2, 1.7);
	//ThresholdImage.ShowImage("res");


	// Usuniecie tla
	Image1CH NewImg(1600, 1200);
	NewImg = ThresholdImage;
	NewImg(0, 0).Intensity() = 0.8;
	for (int i = 1; i < ThresholdImage.width() - 1; i++){
		for (int j = 1; j < ThresholdImage.height() - 1; j++)
		{
			if (ThresholdImage(i, j).Intensity() == 0) {
				if (NewImg(i - 1, j - 1).Intensity() == 0.8)
					NewImg(i, j).Intensity() = 0.8;
				else if (NewImg(i - 1, j).Intensity() == 0.8)
					NewImg(i, j).Intensity() = 0.8;
				else if (NewImg(i - 1, j + 1).Intensity() == 0.8)
					NewImg(i, j).Intensity() = 0.8;
				else if (NewImg(i, j - 1).Intensity() == 0.8)
					NewImg(i, j).Intensity() = 0.8;
				else if (NewImg(i, j + 1).Intensity() == 0.8)
					NewImg(i, j).Intensity() = 0.8;
				else if (NewImg(i + 1, j - 1).Intensity() == 0.8)
					NewImg(i, j).Intensity() = 0.8;
				else if (NewImg(i + 1, j).Intensity() == 0.8)
					NewImg(i, j).Intensity() = 0.8;
				else if (NewImg(i + 1, j + 1).Intensity() == 0.8)
					NewImg(i, j).Intensity() = 0.8;
			}
		}
	}

	//NewImg.ShowImage("New");
	//

	ThresholdImage = NewImg;

	Image1CH NewImg2(1600, 1200);
	NewImg2 = NewImg;
	for (int j = ThresholdImage.height() - 2; j > 0; j = j - 1)
	{
		for (int i = ThresholdImage.width() - 2; i > 0; i = i - 1){

			if (ThresholdImage(i, j).Intensity() == 0) {
				if (NewImg2(i - 1, j - 1).Intensity() == 0.8)
					NewImg2(i, j).Intensity() = 0.8;
				else if (NewImg2(i - 1, j).Intensity() == 0.8)
					NewImg2(i, j).Intensity() = 0.8;
				else if (NewImg2(i - 1, j + 1).Intensity() == 0.8)
					NewImg2(i, j).Intensity() = 0.8;
				else if (NewImg2(i, j - 1).Intensity() == 0.8)
					NewImg2(i, j).Intensity() = 0.8;
				else if (NewImg2(i, j + 1).Intensity() == 0.8)
					NewImg2(i, j).Intensity() = 0.8;
				else if (NewImg2(i + 1, j - 1).Intensity() == 0.8)
					NewImg2(i, j).Intensity() = 0.8;
				else if (NewImg2(i + 1, j).Intensity() == 0.8)
					NewImg2(i, j).Intensity() = 0.8;
				else if (NewImg2(i + 1, j + 1).Intensity() == 0.8)
					NewImg2(i, j).Intensity() = 0.8;
			}
		}
	}
	//NewImg2.ShowImage("New");
	for (int i = 1; i < ThresholdImage.width() - 1; i++){
		for (int j = 1; j < ThresholdImage.height() - 1; j++)
		{
			if (NewImg2(i, j).Intensity() == 0.8)
				NewImg2(i, j).Intensity() = 1;
		}
	}
	//NewImg2.ShowImage("New");

	int **array_of_labels = new int*[1600];
	for (int i = 0; i < 1600; ++i) {
		array_of_labels[i] = new int[1200];
	}

	Image1CH DummyImage1(1600, 1200);
	Image1CH DummyImage2(1600, 1200);

	// Segmentacja 
	int count1 = 0;
	for (int i = 0; i < 1600; i++)
	{
		for (int j = 0; j < 1200; j++)
		{
			if (ThresholdImage(i, j).Intensity() == 0)
			{
				count1 = count1 + 1;
				array_of_labels[i][j] = count1;
			}
			else
				array_of_labels[i][j] = 0;
		}
	}

	int small_array[3][3];
	for (int i = 1; i < 1599; i++)

	{
		for (int j = 1; j < 1199; j++)

		{
			if (array_of_labels[i][j] != 0)
			{

				for (int a = -1; a < 2; a++){
					for (int b = -1; b < 2; b++){
						small_array[a + 1][b + 1] = array_of_labels[i + a][j + b];

					}
				}
				array_of_labels[i][j] = minimum_nonzero(small_array);
			}
		}
	}


	for (int i = 1598; i > 0; i--)
	{
		for (int j = 1198; j > 0; j--)
		{
			if (array_of_labels[i][j] != 0)
			{

				for (int a = -1; a < 2; a++){
					for (int b = -1; b < 2; b++){
						small_array[a + 1][b + 1] = array_of_labels[i + a][j + b];
					}
				}
				array_of_labels[i][j] = minimum_nonzero(small_array);
			}
		}
	}



	int *array_for_Seg_removal;
	array_for_Seg_removal = new int[1920000];
	for (int i = 0; i < 1920000; i++)
	{
		array_for_Seg_removal[i] = 0;
	}


	for (int i = 0; i < 1600; i++)
	{
		for (int j = 0; j < 1200; j++)
		{
			array_for_Seg_removal[array_of_labels[i][j]] = array_for_Seg_removal[array_of_labels[i][j]] + 1;

		}


	}

	// Usun segmenty dluzsze niz 100 pikseli. Stworz obraz koncowy.
	for (int i = 1; i < 1500; i++){
		for (int j = 1; j < 1200; j++){
			if (array_of_labels[i][j] != 0){
				if (array_of_labels[i][j] == array_of_labels[i + 100][j])
					array_for_Seg_removal[array_of_labels[i][j]] = 0;
			}
		}
	}

	// Usun segmenty o polu powierzchni mniejszym niz 800 pikseli
	for (int i = 0; i < 1600; i++){
		for (int j = 0; j < 1200; j++){
			if (array_for_Seg_removal[array_of_labels[i][j]] < 800)
				array_of_labels[i][j] = 0;


		}
	}

	delete[] array_for_Seg_removal;


	for (int i = 1; i < 1600; i++){
		for (int j = 1; j < 1200; j++){
			if (array_of_labels[i][j] == 0)
				DummyImage1(i, j).Intensity() = 0;
			else
				DummyImage1(i, j).Intensity() = 1;

		}
	}

	DummyImage1.ShowImage("res");





	int counter = 0;
	int *current;
	current = new int[26];
	for (int i = 0; i < 26; i++)
	{
		current[i] = 0;
	}

	// Liczenie segmentow
	for (int i = 50; i < 1550; i++){
		for (int j = 50; j < 1150; j++){
			if (array_of_labels[i][j] != 0){
				if (present_or_not(current, array_of_labels[i][j]) == 1)
				{
					current[counter] = array_of_labels[i][j];
					counter = counter + 1;
				}

			}

		}
	}

	for (int i = 0; i < 1600; i++){
		for (int j = 0; j < 1200; j++){
			if (array_of_labels[i][j] != 0){
				for (int k = 0; k < 26; k++){
					if (array_of_labels[i][j] == current[k]){
						array_of_labels[i][j] = k + 1;
					}
				}
			}
		}

	}


	delete[] current;



	// Wyznaczenie kwadratu w ktorym zamykaja sie segmenty
	int low_x, high_x, low_y, high_y;


	int bounding_box[26][5];

	for (int seg = 1; seg < 27; seg++)

	{
		low_x = 999999;
		low_y = 999999;
		high_x = 0;
		high_y = 0;


		for (int i = 0; i < 1600; i++)

		{
			for (int j = 0; j < 1200; j++)

			{
				if (array_of_labels[i][j] == seg)

				{
					if (low_x > i)
					{
						low_x = i;
					}

					if (high_x < i)
					{
						high_x = i;
					}

					if (low_y > j)
					{
						low_y = j;
					}

					if (high_y < j)
					{
						high_y = j;
					}

				}
			}
		}

		bounding_box[seg - 1][0] = seg;
		bounding_box[seg - 1][1] = low_x;
		bounding_box[seg - 1][2] = high_x;
		bounding_box[seg - 1][3] = low_y;
		bounding_box[seg - 1][4] = high_y;

	}



	//DummyImage1.ShowImage("Dummy");

	Image3CH Segments(1600, 1200);

	for (int i = 0; i < 1600; i++){
		for (int j = 0; j < 1200; j++){
			if (array_of_labels[i][j] != 0){
				Segments(i, j).Red() = 1.0 *  (float(array_of_labels[i][j]) / 26);
				Segments(i, j).Green() = 1 - (1.0*(float(array_of_labels[i][j]) / 26));
				Segments(i, j).Blue() = 1 - (0.5*(float(array_of_labels[i][j]) / 26));
			}
		}
	}
	//Segments.ShowImage("res");

	// Indentyfikacja segmentow (intensywnosc koloru niebieskiego razy 100 to numer segmentu) //
	for (int i = 0; i < 1600; i++){
		for (int j = 0; j < 1200; j++){
			if (array_of_labels[i][j] != 0){
				Segments(i, j).Blue() = (0.01*(float(array_of_labels[i][j])));
			}
		}
	}
	Segments.ShowImage("res");


	// ======================================================Cechy===================================================//
	// Litery do porównania    //
	char letters[] = { 'd', 'o', 'k', 'w', 'i', 'ó', 'c', 'r', 'a', 'g', 'a', 't', 'w', 'o', 'y', 'r', 'y', 'a', 'g', 'b', 'u', 'r', 'z', 'o', 'z', 'n' };

	// Oblicz pole powierzchni //
	int s_area[26] = { 0 };
	for (int i = 0; i < 26; i++){
		s_area[i] = surface_area(bounding_box[i][1], bounding_box[i][2], bounding_box[i][3], bounding_box[i][4], array_of_labels);
	}

	// Porownaj pole powierzchni i typ litery //
	//for (int i = 0; i < 26; i++){
	//	std::cout << '\n' << letters[i] << '\t' << s_area[i];
	//}
	// Sortuj litery wg pola powierzchni //




	// Oblicz numer Eulera
	int euler_list[26] = { 0 };
	for (int i = 0; i < 26; i++){
		euler_list[i] = euler(bounding_box[i][1], bounding_box[i][2], bounding_box[i][3], bounding_box[i][4], array_of_labels);
	}

	// oblicz proporcje bia³ych pikseli do czarnych
	double proportion_b_t_w[26];
	for (int i = 0; i < 26; i++){
		proportion_b_t_w[i] = proportion_of_area(bounding_box[i][1], bounding_box[i][2], bounding_box[i][3], bounding_box[i][4], array_of_labels);
	}


	//int sorted_sizes[26] = { 999999 };

	
	arrange(s_area, euler_list, proportion_b_t_w);



	for (int i = 0; i < 1600; ++i) {
		delete[] array_of_labels[i];
	}
	delete[] array_of_labels;


	// Przypisz litery segmentom

	char arranged_letters[26];

	for (int i = 0; i < 26; i++){
		arranged_letters[i] = assign_letters(s_area[i], proportion_b_t_w[i], euler_list[i], i);
	}

	// Odczytaj wszystkie slowa pionowe
	string words;
	string word;
	int top = 0;
	int highest;
	int leftmost;

	bool considered_letters[26] = {false};
	bool found = false;

	for (int k = 0; k < 26; k++){
		highest = 9999999;
		for (int i = 0; i < 26; i++){
			if (bounding_box[i][3] < highest && considered_letters[i] == false){
				highest = bounding_box[i][3];
				top = i;
			}
		}
		considered_letters[top] = true;
		word.erase();
		word += arranged_letters[top];
		for (int j = 0; j < 26; j++){
			found = false;
			
			for (int i = 0; i < 26; i++){
				if (i != top){
					if (bounding_box[i][3] - bounding_box[top][4] < 90 && bounding_box[i][3] - bounding_box[top][4] > 0){
						if (bounding_box[top][1] - bounding_box[i][1] < 40 && bounding_box[top][1] - bounding_box[i][1] > -40){
							top = i;
							found = true;
							considered_letters[i] = true;
							word += arranged_letters[top];
						}
					}
				}
			}
			if (found = false){
				break;
			}

		}
		if (word.length() > 1)
			words += word + " ";

	}

	// Znajdowanie pionowych slow

	for (int h = 0; h < 26; h++){
		considered_letters[h] = false;
	}
	for (int k = 0; k < 26; k++){
		leftmost = 9999999;
		for (int i = 0; i < 26; i++){
			if (bounding_box[i][1] < leftmost && considered_letters[i] == false){
				leftmost = bounding_box[i][1];
				top = i;
			}
		}
		considered_letters[top] = true;
		word.erase();
		word += arranged_letters[top];
		for (int j = 0; j < 26; j++){
			found = false;

			for (int i = 0; i < 26; i++){
				if (i != top){
					if (bounding_box[i][1] - bounding_box[top][2] < 120 && bounding_box[i][1] - bounding_box[top][2] > 0){
						if (bounding_box[top][4] - bounding_box[i][4] < 70 && bounding_box[top][4] - bounding_box[i][4] > -70){
							top = i;
							found = true;
							considered_letters[i] = true;
							word += arranged_letters[top];
						}
					}
				}
			}
			if (found = false){
				break;
			}

		}
		if (word.length() > 1)
			words += word + " ";

	}
	cout << "Znalezione slowa: "<< words << endl << endl;

	string word_base[47] = {
		"tchórz",
		"gwar",
		"mydło",
		"ciało",
		"pies",
		"kot",
		"woda",
		"hamulec",
		"powietrze",
		"kamera",
		"ziemia",
		"telefon",
		"kura",
		"zołza",
		"łysin",
		"hyź",
		"kabzo",
		"gis",
		"muzy",
		"łachę",
		"wieje",
		"rów",
		"rum",
		"zazółć",
		"zgańmy",
		"gdy",
		"me",
		"gdy",
		"dyb",
		"latami",
		"pies",
		"kaźń",
		"ogar",
		"guzik",
		"worek",
		"ławica",
		"brać",
		"grypa",
		"twarz",
		"wór",
		"gbur",
		"gryzon",
		"widok",
		"orka",
		"jaźń",
		"kogut",
		"zółw"
	};

	cout << "Nieznalezione slowa:" << endl;
	for (int i = 0; i < 47; i++){
		if (words.find(word_base[i])==string::npos){
			cout << word_base[i] << endl;
		}
	}

	cout << "Wpisz cokolwiek zeby zamknac program" << endl;
	string whatever;
	cin >> whatever;


	return 0;
}


