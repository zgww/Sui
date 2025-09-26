
#include "./UnitOpengl.h"
#include "./Sgl_orc.h"



void  Sgl$Test$draw(Sgl$Test *  self){
    // printf("TestDraw\n");


    // self->vbo->bind(self->vbo);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // self->cbo->bind(self->cbo);
    // glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(1);
    static bool inited = false;
    static GLuint vao = 0;
    // static GLuint framebuffer = 0;
    if (!inited){
        inited = true;

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        self->vbo->vaIndex = 0;
        self->vbo->elementCount = 3;
        self->vbo->setVertexAttrib(self->vbo);

        self->cbo->vaIndex = 1;
        self->cbo->elementCount = 4;
        self->cbo->setVertexAttrib(self->cbo);

        self->tbo->vaIndex = 2;
        self->tbo->elementCount = 2;
        self->tbo->setVertexAttrib(self->tbo);

        self->ibo->bind(self->ibo);


        glBindVertexArray(0);

        // self->tex->active(self->tex, 1);
        // self->tex->bind(self->tex);


        // glGenFramebuffers(1, &framebuffer);
        // glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        // self->fbo->bind(self->fbo);

        // // 生成纹理
        // unsigned int texColorBuffer;
        // glGenTextures(1, &texColorBuffer);
        // glBindTexture(GL_TEXTURE_2D, texColorBuffer);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // glBindTexture(GL_TEXTURE_2D, 0);

        // Sgl$fboTex = texColorBuffer;

        // // 将它附加到当前绑定的帧缓冲对象
        // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);  


        // unsigned int rbo;
        // glGenRenderbuffers(1, &rbo);
        // glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
        // glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);  
        // glBindRenderbuffer(GL_RENDERBUFFER, 0);
        // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

        // if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        //     printf("Frame Buffer ststatu fail\n");
        // }
        // glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    // glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    self->fbo->bind(self->fbo);

    glViewport(0, 0, 800, 600);
    glClearColor(.06f, 0.96f, 0.96f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);


    self->program->use(self->program);
    glBindVertexArray(vao);

    self->tex->active(self->tex, 1);
    self->tex->bind(self->tex);


    self->program->uniform1i(self->program, "tex", 1);
    self->program->uniform4f(self->program, "uColor", 1.0, 1.0, 0.4, 1.0);


    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // self->tex->unbind(self->tex);
    glBindVertexArray(0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0); // 返回默认
    // self->fbo->unbind(self->fbo);
    //wireframe
    // glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
}
void  Sgl$TestDraw$draw(Sgl$TestDraw *  self){
    // printf("TestDraw2\n");

    // glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    self->fbo->bind(self->fbo);

    glViewport(0, 0, 800, 600);
    glClearColor(.06f, 0.96f, 0.96f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glDisable(GL_CULL_FACE);

		// glDisable(GL_CULL_FACE);
		// glDisable(GL_DEPTH_TEST);
		// glDisable(GL_SCISSOR_TEST);
		// glDisable(GL_STENCIL_TEST);
		// glDisable(GL_ALPHA_TEST);


    // self->program->use(self->program);
    // self->drawObj->vao->bind(self->drawObj->vao);
    // glBindVertexArray(vao);
    self->drawObj->use(self->drawObj);

    // self->tex->active(self->tex, 1);
    // self->tex->bind(self->tex);

    // auto p = self->drawObj->material->program;
    // p->uniform1i(p, "tex", 1);

    // Sgl$Mat *m = &self->drawObj->material->projection;
    // Sgl$Mat$perspective(m, 45 / 180.0 * 3.1415926, 1.0, 0.1, 1000);

    Sgl$Mat *m = &self->drawObj->material->model;
    // Sgl$Mat$translate(m, 0, 0, -0.1);
    // Sgl$Mat$rotateZ(m, 0.01);

    self->drawObj->material->updateUniforms(self->drawObj->material);
    // p->uniform4f(p, "uColor", 1.0, 1.0, 0.4, 1.0);


    // glDrawArrays(GL_TRIANGLES, 0, 6);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    auto ibo = self->drawObj->geometry->ibo;
    int indexCount = ibo->calcIndexCount(ibo);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    // self->tex->unbind(self->tex);
    glBindVertexArray(0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0); // 返回默认
    // self->fbo->unbind(self->fbo);
    //wireframe
    // glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
}