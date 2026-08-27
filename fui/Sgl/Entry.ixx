
#include <stdio.h>
#include "Core/App.h"
#include "Core/Window.h"
#include "Core/View.h"
#include "View/TextView.h"
#include "Layout/LayoutLinear.h"

import Sgl;

int main() {
	printf("hi'\n");
	urgc.start_process_thread();

	auto app = App_use();

	auto root = Ref(new LayoutLinear());
	RINS(root.get()) {
		o.backgroundColor = 0xffefefef;

		o.jcc().aic();
		R(TextView) { o.setText("你123好啊"); } REND;


		auto win = Ref(new Window());
		win->setRootView(&o);
		win->setTitle("1测试Entry.ixx");
		win->setSize(800, 600);
		win->show();
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
	app->runEventLoop();
	return 0;
}