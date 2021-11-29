#include <memory>
#include <string>

#include <imgui.h>

#include "application.h"
#include "model.h"
#include "shader.h"
#include "light.h"
#include "camera.h"
#include "skybox.h"
#include "texture.h"

#include "scene.h"

class Client: public Application {
public:
    Client();

    ~Client();

    void handleInput() override;

    void renderFrame() override;
private:
    std::unique_ptr<Scene> _scene;
    std::unique_ptr<Renderer> _renderer;
    std::vector<std::shared_ptr<Camera>> _cameras;
};