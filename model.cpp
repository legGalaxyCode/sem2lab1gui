#include<model.h>

Model* Model::model = nullptr;

Model* Model::getInstance() {
    if (model == nullptr) {
        model = new Model; //pass args if needed
    }
    return model;
}

Model::Model(){};
