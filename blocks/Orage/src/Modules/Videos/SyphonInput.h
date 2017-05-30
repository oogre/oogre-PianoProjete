//
//  SyphonInput.hpp
//  PianoProjete
//
//  Created by Vincent Evrard on 2017-05-29.
//
//

#ifndef SyphonInput_hpp
#define SyphonInput_hpp


#include "ModuleVideo.h"
#include "cinderSyphon.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {
    class SyphonInput : public ModuleVideo{
        gl::Context * mMainWinCtx;
        map <string, WindowCanvasRef> windowCanvas;
        gl::FboRef			mFbo;
        
        
        syphonClient * clientRef;
        syphonServerDirectory * serverDir;
        int dirIdx;
        void keyDown( KeyEvent event );
        void nextClient();
        void setClient(int _idx);
        
        SyphonInput(string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx);
    public:
        static int COUNT;
        static int winOutCOUNT;
        ~SyphonInput(){
            mFbo.reset();
            mMainWinCtx = nullptr;
        }
        
        typedef std::shared_ptr<class SyphonInput> SyphonInputRef;
        
        static SyphonInputRef create( const std::string name, vec2 origin, gl::Context * mMainWinCtx)
        {
            SyphonInput::COUNT++;
            return SyphonInputRef( new SyphonInput( name, origin, vec2(WIDTH, 580),  mMainWinCtx ) );
        }
        
        
        void setupShader() override;
        void setupUI() override;
        void setup() override;
        void update() override;
        void createOutputWindow();
    };
    
    typedef std::shared_ptr<class SyphonInput> SyphonInputRef;
}


#endif /* SyphonInput_hpp */
