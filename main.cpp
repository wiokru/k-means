#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <math.h>
#include "point.h"

using namespace std;

int find_min_centroid(pair<double, int> *dist, int size){
    int min_in = dist[0].second;
    double min_dist = dist[0].first;
    for(int i=1; i<size; i++){
        if(dist[i].first < min_dist){
            min_dist = dist[i].first;
            min_in = dist[i].second;
        }
    }

    return min_in;
}

int main()
{
    //stringstream ss;
    ifstream input ("/home/wiokru/Dokumenty/sztuczna_inteligencja2/4_zadanie/plik1.txt");
    ofstream output ("/home/wiokru/Dokumenty/sztuczna_inteligencja2/4_zadanie/result_file.txt");

    vector<Point*> points;
    double x, y;
    int cent_count=0;;
    string color, info;
    string line, temp;

    if(input.is_open()){
        while(getline(input,line)){
            string::iterator it=line.begin();
            while(*it != ' '){ //pobranie x
                temp.push_back(*it);
                it++;
            }
            x=(double)atof(temp.c_str());
            it++;
            temp.clear();
            while(*it != ' '){ //pobranie y
                temp.push_back(*it);
                it++;
            }
            y=(double)atof(temp.c_str());
            it++;
            temp.clear();
            color = *it; //pobranie koloru
            it++; it++;
            if (it==line.end()) //jesli dalej juz nic nie ma to tworze pkt
                points.push_back(new Point(x, y, color));
            else{   //jesli jest ta gwiazdeczka, to ja dodaje i tworze pkt "specjalny"
                info = *it;
                cent_count++;
                points.push_back(new Point(x, y, color, info));
            }
        }
        input.close();
    }
    else
        cerr<<"PLIK NIE ISTNIEJE"<<endl;

    //****************************************************************************************

    vector<Point*> centroids;
    int centroids_count;
    for (vector<Point*>::iterator it=points.begin(); it!=points.end(); it++){
        if((*it)->getSpecial()=="*"){
            centroids.push_back(*it);
            centroids_count++;
        }
    }
    for(int i=0; i<centroids_count; i++){
        if(i==0) centroids[0]->changeColor("R");        //przypisuje centroidom kolory
        if(i==1) centroids[1]->changeColor("G");
        if(i==2) centroids[2]->changeColor("B");
    }

    vector<Point*> *splited;                            //tworze tyle wektorów ile mam centroidow
    splited=new vector<Point*> [centroids_count];
    while(true){
      splited->clear();
        for (int p=0; p<points.size(); p++ ){
            pair <double, int> distances[centroids_count];
            if(points[p]->getSpecial() != "*"){
                for (int c=0; c<centroids_count; c++ ){
                    double distance = sqrt((points[p]->getX()-centroids[c]->getX())*(points[p]->getX()-centroids[c]->getX())+((points[p]->getY()-centroids[c]->getY())*(points[p]->getY()-centroids[c]->getY())));
                    distances[c].first = distance;  //zapisuje odleglosci miedzy centroidami a pkt
                    distances[c].second = c;
                }
                int min_ind = find_min_centroid(distances, centroids_count);
                points[p]->changeColor(centroids[min_ind]->getColor());
                splited[min_ind].push_back(points[p]);
//                cout<<min_ind<<"===="<<splited[min_ind].back()->getX()<<endl;
            }
        }

        double new_x;
        double new_y;
        bool is_XY_equal[centroids_count] = {false};
        int equal_count = 0;

        for(int i=0; i<centroids_count; i++){  //dla kazdego centroidu sprawdzam sasiadow zeby policzyc srodek
            double x_sum=0;
            double y_sum=0;
            for(vector<Point*>::iterator nbh=splited[i].begin(); nbh!=splited[i].end(); nbh++ ){
                x_sum+=(*nbh)->getX();
                y_sum+=(*nbh)->getY();
            }

            new_x = x_sum/splited[i].size();
            new_y = y_sum/splited[i].size();

            if(new_x==centroids[i]->getX() && new_y==centroids[i]->getY()){
                is_XY_equal[i]=true;
                //break;
            }
            else{
                centroids[i]->setX(new_x);
                centroids[i]->setY(new_y);
            }
        }

        for(int i=0; i<centroids_count; i++){ //jesli znajdzie centroid ktory byl zmieniony to przerywa
           if(is_XY_equal[i]==true) equal_count++;
        }
        if(equal_count == centroids.size()){
            break;
        }
        else{
            for(int i=0; i<centroids.size(); i++)
                splited[i].clear();
        }

    }
    points.clear();

    for (int i=0; i<centroids.size(); i++){
        for(vector<Point*>::iterator it=splited[i].begin(); it!=splited[i].end(); it++)
            points.push_back(*it);
    }
    for (vector<Point*>::iterator c_it=centroids.begin(); c_it!=centroids.end(); c_it++)
        points.push_back(*c_it);

    //****************************************************************************************

    if(output.is_open()){

        for (vector<Point*>::iterator it=points.begin(); it!=points.end(); it++ ){
            output << (*it)->pointToString();
            cout<<"Zapisano zmieniony punkt."<<endl;
        }
        output.close();
    }
    else
        cout<<"BLAD ZAPISU"<<endl;

    return 0;
}
