#include "extracter.h"

std::list<std::vector<int> > extracter(int argc, char** argv){
    std::string coord = argv[0];
    string result_name = coord + "/red_result.txt";
    //std::ifstream fin(coord);
    std::ifstream fin;
    fin.open(result_name);


/*    fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        fin.open(coord);
	cout << "kappa" << endl;
    } catch (std::system_error& e) {
	cout << "marche pas ouin" << endl;
        std::cout << e.code().message() << std::endl;
    }*/

    std::string line;
    std::string linebis;
    std::string to;
    std::string name;
    int xMin, width, yMin, height;
    std::list< std::vector<int> > list_coord;

    //cout << "buffer : " << fin.rdbuf() << endl;
    cout << argv[0] << endl;
    cout << argv[1] << endl;

    for ( int i = 1; i <= 1; i++ ) {
    const char comma = ',';
    int compteur = 0;
    int compteurbis = 0;
    int compteur_image = 0;
    cout << "it should" << endl;
    while (getline(fin, line, comma))
    {
	cout << "seems legit" << endl;
        if(compteur == 3) {
            compteurbis = 0;
            std::stringstream ss(line);
                    while(std::getline(ss,to,'\n')){
                    std::istringstream iss (to);
                    switch(compteurbis) {
                    case 0:
                        {
                        iss >> height;
                        compteurbis = 1;

                        // Read img
                        cv::Mat img = cv::imread("./1550106247/1550106247.30.png");
			if (img.size == 0) {
				cout << "Image could not be found" << endl;
			}
			cout << "maybe" << endl;
                        cv::Mat croppedImg;

                        // This line picks out the rectangle from the image
                        // and copies to a new Mat
                        img(cv::Rect(xMin,yMin,width,height)).copyTo(croppedImg);
                        list_coord.push_back({xMin,yMin,width,height});
                        // Display diff (no more necessary)
                        //cv::imshow( "Cropped Image",  croppedImg);

			//rajouter ce compteur si on traite plusieurs images
                        //std::stringstream ss;
                        //ss << i;
                        //std::string compteur_string = ss.str();
                        std::stringstream ssbis;
                        ssbis << compteur_image;
                        std::string compteur_image_string = ssbis.str();
			cout << compteur_image_string << endl;
                        name = coord + "/image"+ compteur_image_string + ".jpeg";
                        compteur_image++;
                        cv::imwrite(name, croppedImg);

                        break;
                        }
                    case 1:
                        iss >> xMin;
                        compteurbis = 0;
                        break;
                    default:
                        std::cout << "end of line bug";
                    }
                    }
            }
        else {
                std::istringstream issbis (line);
                switch(compteur) {
                    case 0:
                        issbis >> xMin;
                        break;
                    case 1:
                        issbis >> yMin;
                        break;
                    case 2:
                        issbis >> width;
                        break;
                    }
            }
        compteur++;
        compteur = compteur %4;
        if(compteur == 0) {
           compteur++;
        }
    }
    }
    fin.close();
    return list_coord;
}
/*int main(int argc, char** argv)
{
    extracter(argc, argv);
  return 0;
}*/
