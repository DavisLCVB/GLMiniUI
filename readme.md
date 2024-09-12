# OpenGL Minimal User Interface

GLMiniUI es una librería para crear botones y etiquetas de texto utilizando OpenGl y FreeType en c++.

## Información

La librería proporciona 3 clases principales:

- Label: Permite crear etiquetas de texto y personalizar sus atributos
- Button: Crea botones personalizables y se les puede colocar una etiqueta en su interior
- ButtonManager (beta): Permite gestionar de una manera más sencilla los eventos de los botones

> [!NOTE]
> Revisa el [ejemplo](./examples/demo.cpp) para obtener más detalles

## Dependencias

Se utiliza [OpenGL](https://github.com/KhronosGroup/OpenGL-Registry?tab=readme-ov-file) para el dibujado en pantalla y [Freetype](https://gitlab.freedesktop.org/freetype/freetype) para cargar los bitmaps de las fuentes para su posterior dibujado con OpenGL por lo que se recomienda tener instaladas ambas librerías.

Además se usa [CMake](https://cmake.org/) para construir la librería por lo que si se desea compilarla manualmente es necesario este programa.

## Uso

Puede descargar la librería precompilada del apartado de versiones o compilarlo manualmente con los siguiente comandos

```sh
mkdir build
cd ./build
cmake ..
cmake --build -j 10
```

Esto generará el archivo de librería estática y un ejecutable del [ejemplo](examples/demo.cpp)
