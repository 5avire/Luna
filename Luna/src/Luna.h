#pragma once

// -- Core --
#include <Luna/Core/Core.h>
#include <Luna/Core/Timestep.h>
// -- Core --

// -- Application --
#include <Luna/Core/Application.h>
// -- Application --

// -- Application Layers --
#include <Luna/Core/Layer.h>
#include <Luna/ImGui/ImGuiLayer.h>
// -- Application Layers --

// -- Inputs --
#include <Luna/Core/Input.h>
#include <Luna/Core/KeyCodes.h>
#include <Luna/Core/MouseButtonCodes.h>
// -- Inputs --

// -- Rendering --
// -- API Stuff --
#include <Luna/Renderer/Renderer.h>
#include <Luna/Renderer/RenderCommand.h>

// -- Resources --
#include <Luna/Renderer/Buffer.h>
#include <Luna/Renderer/Shader.h>
#include <Luna/Renderer/Camera.h>
#include <Luna/Renderer/Texture.h>
#include <Luna/Renderer/VertexArray.h>
#include <Luna/Renderer/CameraController.h>
// -- Rendering --

// -- Logging ---
// Bugs out without ostr sometimes
#include <spdlog/fmt/ostr.h>
#include <Luna/Core/Log.h>
// -- Logging ---
