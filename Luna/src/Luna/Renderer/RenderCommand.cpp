#include <lunapch.h>
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Luna {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
