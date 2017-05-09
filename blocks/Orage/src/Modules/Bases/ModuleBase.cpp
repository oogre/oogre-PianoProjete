//
//  ModuleBase.cpp
//  ORAGE2
//
//  Created by Vincent Evrard on 2017-05-05.
//
//

#include "ModuleBase.h"


namespace ogre {

int ModuleCommon::ID = 0;

cinder::gl::TextureRef    ModuleCommon::CLOSE;

template<typename DataType>
ModuleBase<DataType>::ModuleBase(const std::string name, vec2 origin, vec2 size, const int & nInput, const int & nOutput ):ModuleCommon(name, origin, size){
    
    for(int i = 0 ; i < nInput ; i ++){
        char current = ((char)((int)'A'+i));
        inputs[current] = nullptr;
    }
    for(int i = 0 ; i < nOutput ; i ++){
        char current = ((char)((int)'A'+i));
        outputs[current] = nullptr;
    }
}

template<typename DataType>
void ModuleBase<DataType>::setupInput(){
    string s = inputs.size()>1?"s": "";
    auto it = inputs.begin(), end = inputs.end();
    string moduleName = this->name;
    
    for( ; it != end ; it ++){
        ButtonRef b = Button::create( "Input "+to_string(it->first), false, Button::Format().label(false));
        b->setSize( vec2( 25, 25 ) );
        inputBtns.push_back(b);
        if(it == inputs.begin()){
            LabelRef l = Label::create("inputs", "Input"+s+" : ", FontSize::SMALL);
            mUi->addSubViewDown(l);
            mUi->addSubViewToHeader(l);
        }
        mUi->addSubViewRight(b);
        mUi->addSubViewToHeader(b);
    }
}

template<typename DataType>
void ModuleBase<DataType>::setupOutput(){
    string s = outputs.size()>1?"s": "";
    auto it = outputs.begin(), end = outputs.end();
    string moduleName = this->name;
    for( ; it != end ; it ++){

        ButtonRef b = Button::create( "Output "+to_string(it->first), false, Button::Format().label(false));
        b->setSize( vec2( 25, 25 ) );
        outputBtns.push_back(b);
        
        if(it == outputs.begin()){
            LabelRef l = Label::create("outputs", "Output"+s+" : ", FontSize::SMALL);
            mUi->addSubViewDown(l);
            mUi->addSubViewToHeader(l);
        }
        mUi->addSubViewRight(b);
        mUi->addSubViewToHeader(b);
    }
}

template<typename DataType>
void ModuleBase<DataType>::setupUI(){
    ModuleCommon::setupUI();
}

template<typename DataType>
void ModuleBase<DataType>::setup(){
    ModuleCommon::setup();
}

template<typename DataType>
void ModuleBase<DataType>::update(){
    ModuleCommon::update();
}

    template class ModuleBase<NotesetRef>;
    template class ModuleBase<gl::Texture2dRef>;

    
}
