#include "InitHelper.hpp"
#include "glew.h"
#include "freeglut.h"
#include <iostream>

const char *WINDOW_NAME = "Sivax Extreme Engine";

void init_Glut_Glew(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitContextVersion(4, 4);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutSetOption(
            GLUT_ACTION_ON_WINDOW_CLOSE,
            GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(WINDOW_NAME);
    glutPositionWindow(550, 10);
    glewExperimental = GL_TRUE;
    GLenum GlewInitResult = glewInit();
    if (GlewInitResult != GLEW_OK) {
        std::cout << "ERROR: " << glewGetErrorString(GlewInitResult);
    }
}

void inicializarConsola() {
    std::cout << std::endl;
    std::cout << "      :::::::: ::::::::::: :::     :::     :::     :::    :::                          " << std::endl;
    std::cout << "    :+:    :+:    :+:     :+:     :+:   :+: :+:   :+:    :+:                           " << std::endl;
    std::cout << "   +:+           +:+     +:+     +:+  +:+   +:+   +:+  +:+                             " << std::endl;
    std::cout << "  +#++:++#++    +#+     +#+     +:+ +#++:++#++:   +#++:+                               " << std::endl;
    std::cout << "        +#+    +#+      +#+   +#+  +#+     +#+  +#+  +#+                               " << std::endl;
    std::cout << "#+#    #+#    #+#       #+#+#+#   #+#     #+# #+#    #+#                               " << std::endl;
    std::cout << "######## ###########     ###     ###     ### ###    ###                                " << std::endl;
    std::cout << "      :::::::::: :::    ::: ::::::::::: :::::::::  ::::::::::   :::   :::   :::::::::: " << std::endl;
    std::cout << "     :+:        :+:    :+:     :+:     :+:    :+: :+:         :+:+: :+:+:  :+:         " << std::endl;
    std::cout << "    +:+         +:+  +:+      +:+     +:+    +:+ +:+        +:+ +:+:+ +:+ +:+          " << std::endl;
    std::cout << "   +#++:++#     +#++:+       +#+     +#++:++#:  +#++:++#   +#+  +:+  +#+ +#++:++#      " << std::endl;
    std::cout << "  +#+         +#+  +#+      +#+     +#+    +#+ +#+        +#+       +#+ +#+            " << std::endl;
    std::cout << " #+#        #+#    #+#     #+#     #+#    #+# #+#        #+#       #+# #+#             " << std::endl;
    std::cout << "########## ###    ###     ###     ###    ### ########## ###       ### ##########       " << std::endl;
    std::cout << "      :::::::::: ::::    :::  :::::::: ::::::::::: ::::    ::: ::::::::::              " << std::endl;
    std::cout << "     :+:        :+:+:   :+: :+:    :+:    :+:     :+:+:   :+: :+:                      " << std::endl;
    std::cout << "    +:+        :+:+:+  +:+ +:+           +:+     :+:+:+  +:+ +:+                       " << std::endl;
    std::cout << "   +#++:++#   +#+ +:+ +#+ :#:           +#+     +#+ +:+ +#+ +#++:++#                   " << std::endl;
    std::cout << "  +#+        +#+  +#+#+# +#+   +#+#    +#+     +#+  +#+#+# +#+                         " << std::endl;
    std::cout << " #+#        #+#   #+#+# #+#    #+#    #+#     #+#   #+#+# #+#                          " << std::endl;
    std::cout << "########## ###    ####  ######## ########### ###    #### ##########                    " << std::endl;
    std::cout << std::endl;
    std::cout << "*******************************************************************************" << std::endl;
    std::cout << "**                                                                           **" << std::endl;
    std::cout << "**  GPU Model:         " << glGetString(GL_RENDERER) << "\t\t\t     **" << std::endl;
    std::cout << "**  OpenGL Version:    " << glGetString(GL_VERSION) << "\t\t\t\t     **" << std::endl;
    std::cout << "**  GLSL Version:      " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\t\t\t     **" << std::endl;
    std::cout << "**  Glew Version:      " << glewGetString(GLEW_VERSION) << "\t\t\t\t\t\t     **" << std::endl;
    std::cout << "**                                                                           **" << std::endl;
    std::cout << "*******************************************************************************" << std::endl;
    std::cout << std::endl;
}

void initFuncionGLs() {
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glPointSize(50.0f);
    //glEnable(GL_CULL_FACE);
    glClearColor(0.25f, 0.25f, 0.25f, 0.0f);
}