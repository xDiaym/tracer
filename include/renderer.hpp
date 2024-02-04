#pragma once

class ImageBuffer;
class Scene;
class Camera;

void render(ImageBuffer &image, const Scene &scene, const Camera &camera);
