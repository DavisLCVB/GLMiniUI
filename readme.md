# OpenGL Minimal User Interface

GLMiniUI es una librería para crear botones y etiquetas de texto utilizando OpenGl y FreeType en `C++`.

## Información

La librería proporciona 3 clases principales:

- Label: Permite crear etiquetas de texto y personalizar sus atributos
- Button: Crea botones personalizables y se les puede colocar una etiqueta en su interior
- ButtonManager (beta): Permite gestionar de una manera más sencilla los eventos de los botones

> [!NOTE]
> Revisa el [ejemplo](./examples/demo.cpp) para obtener más detalles

## Dependencias

Se utiliza [OpenGL](https://github.com/KhronosGroup/OpenGL-Registry?tab=readme-ov-file) para el dibujado en pantalla y [Freetype](https://gitlab.freedesktop.org/freetype/freetype) para cargar los bitmaps de las fuentes para su posterior dibujado con OpenGL por lo que se recomienda tener instaladas ambas librerías.

Además se usa [CMake](https://cmake.org/) para construir la librería y [vcpkg](https://vcpkg.io/en/index.html) para administrar las dependencias por lo que si se desea compilarla manualmente es necesario estos programas.

## Uso

Puede descargar la librería precompilada del apartado de versiones o compilarlo manualmente con los siguiente comandos

```sh
cmake --preset=default
cd build
cmake --build . -j 10
# Opcional
./demo
```

Esto generará el archivo de librería estática y un ejecutable del [ejemplo](examples/demo.cpp)
