//
//  PositionExtractor.cpp
//  ORAGE2
//
//  Created by Vincent Evrard on 2017-05-07.
//
//

#include "PositionExtractor.h"



using namespace ogre;
using namespace cinder;
using namespace cinder::gl;
using namespace std;
using namespace reza::ui;

namespace ogre {
    
    int PositionExtractor::COUNT = 0;
    
    PositionExtractor::PositionExtractor( std::string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx ) : ModulePiano(name+" "+ tools.to_roman(PositionExtractor::COUNT), origin, size, 1, 0){
        this->mMainWinCtx = mMainWinCtx;
    }
    
    void PositionExtractor::setup(){
        ModulePiano::setupUI();
        setupUI();
    }
    
    
    void PositionExtractor::update(){
        
        if(mMainWinCtx != gl::Context::getCurrent()){
            return;
        }
        ModulePiano::update();
        
        if(!inputs['A']){
            return;
        };
        
        if(oldInputID != inputs['A']->ID){
            oldInputID = inputs['A']->ID;
            countRate = inputs['A']->length;
            countOctaveRate = inputs['A']->lengthOneOctave;
            if(countRate!=0){
                auto it = inputs['A']->notes.begin();
                auto end = inputs['A']->notes.end();
                int c = 0;
                for(; it != end ; it++){
                    c+= (*it)->num;
                    minRate = minRate > (*it)->num ? (*it)->num : minRate;
                    maxRate = maxRate < (*it)->num ? (*it)->num : maxRate;
                }
                averageRate = (float)c/countRate;
                middleRate = ( minRate + maxRate ) * .5f;
                medianeRate = minRate + inputs['A']->notes.size() * .5f;
            }else{
                maxRate = 0.f ;
                minRate = Config::NOTE_LEN;
                medianeRate = middleRate = averageRate = Config::NOTE_LEN * 0.5f;
            }
        }
        average += (averageRate - average)*inertie;
        min += (minRate - min)*inertie;
        max += (maxRate - max)*inertie;
        middle += (middleRate - middle)*inertie;
        mediane += (medianeRate - mediane)*inertie;
        count += (countRate - count)*inertie;
        countOctave += (countOctaveRate - countOctave)*inertie;
    }
    
    void PositionExtractor::setupUI(){
        mUi->setColorBack(ColorAT<float>(vec4(.1f, .2f, .3f, .4f)));
        //mUi->setColorFill(ColorAT<float>(vec4(.8f, .9f, 1.f, .6f)));
        mUi->setColorFillHighlight(ColorAT<float>(vec4(.1f, .9f, 1.f, 1.f)));
        
        ModulePiano::setupUI();
        setupInput();
        setupOutput();
        
        tools.addSlider(mUi, "INERTIE", &inertie, 0, 1);
        mUi->addSpacer(false);
        mUi->addSpacer(false);
        
        tools.addSlider(mUi, "count", &count, 0, Config::NOTE_LEN);
        tools.addSlider(mUi, "countOctave", &countOctave, 0, Config::OCTAVE_LEN);
        tools.addSlider(mUi, "min", &min, 0, Config::NOTE_LEN);
        tools.addSlider(mUi, "average", &average, 0, Config::NOTE_LEN);
        tools.addSlider(mUi, "middle", &middle, 0, Config::NOTE_LEN);
        tools.addSlider(mUi, "mediane", &mediane, 0, Config::NOTE_LEN);
        tools.addSlider(mUi, "max", &max, 0, Config::NOTE_LEN);
        
        mUi->setMinified(true);
    }
};