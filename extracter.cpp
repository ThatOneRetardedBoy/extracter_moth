#include "extracter.h"

std::list<std::vector<int>> extracter(int argc, char** argv){
   std::string coord = argv[1];
   std::ifstream fin(coord);

    std::string line;
    std::string linebis;
    std::string to;
    std::string name;
    int xMin, width, yMin, height;
    std::list< std::vector<int> > list_coord;
    for ( int i = 1; i <= argc; i++ ) {
    const char comma = ',';
    int compteur = 0;
    int compteurbis = 0;
    int compteur_image = 0;
    while (getline(fin, line, comma))
    {
        if(compteur == 3) {
            compteurbis = 0;
            std::stringstream ss(line);
                    while(std::getline(ss,to,'\n')){
                    switch(compteurbis) {
                    case 0:
                        {
                        height = std::stoi(to);
                        compteurbis = 1;

                        // Read img
                        cv::Mat img = cv::imread(argv[2]);
                        cv::Mat croppedImg;

                        // This line picks out the rectangle from the image
                        // and copies to a new Mat
                        img(cv::Rect(xMin,yMin,width,height)).copyTo(croppedImg);
                        list_coord.push_back({xMin,yMin,width,height});
                        // Display diff (no more necessary)
                        //cv::imshow( "Cropped Image",  croppedImg);
                        name = "image"+std::to_string(i)+"_"+ std::to_string(compteur_image)+".jpeg";
                        compteur_image++;
                        cv::imwrite(name, croppedImg);

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
                switch(compteur) {
                    case 0:
                        xMin = std::stoi(line);
                        break;
                    case 1:
                        yMin = std::stoi(line);
                        break;
                    case 2:
                        width = std::stoi(line);
                        break;
                    }
            }
        compteur++;
        compteur = compteur %4;
        if(compteur == 0) {

        }
    }
    }
    return list_coord;
}
int main(int argc, char** argv)
{
  return 0;
}