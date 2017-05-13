#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <vector>

struct Data {
    int value;

    Data(int v)
    :   value(v)
    { }
};

class DataHolder {
private:
    std::vector<Data*> data;

public:
    ~DataHolder() {
        for(int i = data.size()-1; i >= 0; i--)
            delete this->data[i];
    }

    void loadData(Data* data) {
        this->data.push_back(data);
    }

    int getMaxY() {
        int maxValue = this->data[0]->value;

        for(int i = 1; i < this->data.size(); i++) {
            if(this->data[i]->value > maxValue)
                maxValue = this->data[i]->value;
        }

        return maxValue;
    }

    int getMaxX() const {
        return this->data.size();
    }

    int getNValue(int n) const {
        return this->data[n]->value;
    }
};

class Graph {
private:
    int maxY;
    int currY;
    int maxX;
    int currX;

public:
    Graph(int mY, int mX)
    :   maxY(mY), maxX(mX), currX(1) {
        this->currY = this->maxY;
    }

    void drawGraph(DataHolder& dHolder) {
        system("cls");
        std::cout<<"Your data graph/structure"<<std::endl;
        std::cout<<"-----------------------------------------------------"<<std::endl<<std::endl;

        //top of the graph
        if(maxY < 10) {
            std::cout<<"y ^"<<std::endl;
            std::cout<<"  |"<<std::endl;
        }
        else {
            std::cout<<"y  ^"<<std::endl;
            std::cout<<"   |"<<std::endl;
        }

        //drawing each line
        for(int i = this->maxY; i >= 1; i--) {
            std::cout<<this->currY;

            //to roll out the y line
            if(maxY >= 10) {
                if(currY >= 10)
                    std::cout<<" |";
                else
                    std::cout<<"  |";
            }
            else
                std::cout<<" |";

            //if x's value is greater or equal to current y, draw it
            for(int i = 0; i < maxX; i++) {
                if(dHolder.getNValue(i) >= currY)
                    std::cout<<"  #";
                else
                    std::cout<<"   ";
            }

            std::cout<<std::endl;

            this->currY--;
        }

        //x line
        for(int i = 1; i <= this->maxX; i++)
            std::cout<<"----";

        std::cout<<">";

        //to roll out the line next to 0
        if(maxY < 10)
            std::cout<<std::endl<<"0 |";
        else
            std::cout<<std::endl<<"0  |";

        //drawing xs
        for(int i = 1; i <= this->maxX; i++) {
            std::cout<<"  "<<this->currX;
            this->currX++;
        }

        //testing stuff
        std::cout<<std::endl<<std::endl<<std::endl;
        for(int i = 0; i < this->maxX; i++) {
            std::cout<<"f("<<i+1<<") = "<<dHolder.getNValue(i)<<std::endl;
        }
    }
};

int main() {
    DataHolder dHolder;
    Graph* graph;
    int dataCount;
    int data;

    std::cout<<"How much data do you want to load: ";
    std::cin>>dataCount;

    srand(time(NULL));
    for(int i = 1; i <= dataCount; i++) {
        data = rand()%26;
        dHolder.loadData(new Data(data));
    }

    graph = new Graph(dHolder.getMaxY(), dHolder.getMaxX());
    graph->drawGraph(dHolder);
    getch();

    delete graph;

    return 0;
}
