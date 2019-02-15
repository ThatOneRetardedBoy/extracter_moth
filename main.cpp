#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>

int main(int argc, char** argv){
   std::string coord = "result.txt";
   std::ifstream fin(coord);

    std::string line;
    std::string linebis;
    std::string to;

    const char comma = ',';
    int compteur = 0;
    int compteurbis = 0;
    int compteur_image = 0;
    std::string name;
    int xMin, xMax, yMin, yMax;
    while (getline(fin, line, comma))
    {
        if(compteur == 3) {
            compteurbis = 0;
            std::stringstream ss(line);
                    while(std::getline(ss,to,'\n')){
                        //std::cout <<"end of line is " << to << '\n';
                        switch(compteurbis) {
                    case 0:
                        {
                        yMax = std::stoi(to);
                        //std::cout << xMin << ' ' << yMin << ' ' << xMax << ' ' << yMax << '\n';
                        compteurbis = 1;

                        // Read img
                        cv::Mat img = cv::imread("1546070602.png");
                        cv::Mat croppedImg;

                        // This line picks out the rectangle from the image
                        // and copies to a new Mat
                        img(cv::Rect(xMin,yMin,xMax,yMax)).copyTo(croppedImg);

                        // Display diff
                        //cv::imshow( "Original Image",  img );
                        cv::imshow( "Cropped Image",  croppedImg);
                        name = "image_"+ std::to_string(compteur_image)+".jpeg";
                        compteur_image++;
                        cv::imwrite(name, croppedImg);
                        //cv::waitKey();

                        break;
                        }
                    case 1:
                        xMin = std::stoi(to);
                        compteurbis = 0;
                        break;
                    default:
                        std::cout << "end of line bug";
                    }
                    }
            }
        else {
                //std::cout <<"compteur"<< compteur<<'\n';
                switch(compteur) {
                    case 0:
                        xMin = std::stoi(line);
                        break;
                    case 1:
                        yMin = std::stoi(line);
                        break;
                    case 2:
                        xMax = std::stoi(line);
                        break;
                    //default:
                        //std::cout << "line bug" << compteurbis << '\n';
                    }
            }
        compteur++;
        compteur = compteur %4;
        if(compteur == 0) {
            compteur++;
        }
}
}

