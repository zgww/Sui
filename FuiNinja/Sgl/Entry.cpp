
#include <stdio.h>
#include "Core/App.h"
#include "Core/Window.h"
#include "Core/View.h"
#include "View/TextView.h"
#include "Layout/LayoutLinear.h"

import Sgl;
import Sgl_Box3;

int main() {
	printf("13hi'\n");
	urgc.start_process_thread();

	auto app = App_use();

	auto root = Ref(new LayoutLinear());
	RINS(root.get()) {
		o.backgroundColor = 0xffefefef;

		o.jcc().aic();
		R(TextView) { o.setText("go whdy什么鬼-l天生"); } REND;


		auto win = Ref(new Window());
		win->setRootView(&o);
		win->setTitle("中文正常吗");
		win->setSize(800, 600);
		win->show();
        printf("get title:%s\n", win->getTitle().c_str());
	} REND;

	Program p;

	p.compile(
		R"EOF(
void main(){
	gl_Position = vec4(0.0);
}
)EOF", R"EOF(
void main(){ 
}
)EOF"
);

	auto drawCtx = Ref(new DrawCtx());
	auto raycaster = Ref(new Raycaster());
	auto pr = Ref(new RgbaPixelsReader());
	auto perspectiveCamera = Ref(new PerspectiveCamera());
	auto particle = Ref(new Particle());
	app->runEventLoop();
	return 0;
}