////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2014 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef CPP3DS_SHADER_HPP
#define CPP3DS_SHADER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cpp3ds/OpenGL.hpp>
#include <cpp3ds/Graphics/Transform.hpp>
#include <cpp3ds/Graphics/Color.hpp>
#include <cpp3ds/System/NonCopyable.hpp>
#include <cpp3ds/System/Vector2.hpp>
#include <cpp3ds/System/Vector3.hpp>
#include <map>
#include <string>
#ifndef EMULATION
#include <3ds.h>
#endif


namespace cpp3ds
{
class InputStream;
class Texture;

////////////////////////////////////////////////////////////
/// \brief Shader class (vertex and fragment)
///
////////////////////////////////////////////////////////////
class Shader : NonCopyable
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Types of shaders
    ///
    ////////////////////////////////////////////////////////////
    enum Type
    {
        Vertex,  ///< Vertex shader
        Geometry, ///< Geometry shader
        Fragment ///< Fragment (pixel) shader
    };

    ////////////////////////////////////////////////////////////
    /// \brief Special type that can be passed to setParameter,
    ///        and that represents the texture of the object being drawn
    ///
    /// \see setParameter(const std::string&, CurrentTextureType)
    ///
    ////////////////////////////////////////////////////////////
    struct CurrentTextureType {};

    ////////////////////////////////////////////////////////////
    /// \brief Represents the texture of the object being drawn
    ///
    /// \see setParameter(const std::string&, CurrentTextureType)
    ///
    ////////////////////////////////////////////////////////////
    static CurrentTextureType CurrentTexture;

public :

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// This constructor creates an invalid shader.
    ///
    ////////////////////////////////////////////////////////////
    Shader();

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~Shader();

    ////////////////////////////////////////////////////////////
    /// \brief Load either the vertex or fragment shader from a file
    ///
    /// This function loads a single shader, either vertex or
    /// fragment, identified by the second argument.
    /// The source must be a text file containing a valid
    /// shader in GLSL language. GLSL is a C-like language
    /// dedicated to OpenGL shaders; you'll probably need to
    /// read a good documentation for it before writing your
    /// own shaders.
    ///
    /// \param filename Path of the vertex or fragment shader file to load
    /// \param type     Type of shader (vertex or fragment)
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    /// \see loadFromMemory, loadFromStream
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromFile(const std::string& filename, Type type);

    ////////////////////////////////////////////////////////////
    /// \brief Load both the vertex and fragment shaders from files
    ///
    /// This function loads both the vertex and the fragment
    /// shaders. If one of them fails to load, the shader is left
    /// empty (the valid shader is unloaded).
    /// The sources must be text files containing valid shaders
    /// in GLSL language. GLSL is a C-like language dedicated to
    /// OpenGL shaders; you'll probably need to read a good documentation
    /// for it before writing your own shaders.
    ///
    /// \param vertexShaderFilename   Path of the vertex shader file to load
    /// \param fragmentShaderFilename Path of the fragment shader file to load
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    /// \see loadFromMemory, loadFromStream
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromFile(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename);

    ////////////////////////////////////////////////////////////
    /// \brief Load either the vertex or fragment shader from a source code in memory
    ///
    /// This function loads a single shader, either vertex or
    /// fragment, identified by the second argument.
    /// The source code must be a valid shader in GLSL language.
    /// GLSL is a C-like language dedicated to OpenGL shaders;
    /// you'll probably need to read a good documentation for
    /// it before writing your own shaders.
    ///
    /// \param shader String containing the source code of the shader
    /// \param type   Type of shader (vertex or fragment)
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    /// \see loadFromFile, loadFromStream
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromMemory(const std::string& shader, Type type);

    ////////////////////////////////////////////////////////////
    /// \brief Load both the vertex and fragment shaders from source codes in memory
    ///
    /// This function loads both the vertex and the fragment
    /// shaders. If one of them fails to load, the shader is left
    /// empty (the valid shader is unloaded).
    /// The sources must be valid shaders in GLSL language. GLSL is
    /// a C-like language dedicated to OpenGL shaders; you'll
    /// probably need to read a good documentation for it before
    /// writing your own shaders.
    ///
    /// \param vertexShader   String containing the source code of the vertex shader
    /// \param fragmentShader String containing the source code of the fragment shader
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    /// \see loadFromFile, loadFromStream
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromMemory(const std::string& vertexShader, const std::string& fragmentShader);

    bool loadFromResource(const std::string& vertexShader, Type type, bool compiled = true);

    ////////////////////////////////////////////////////////////
    /// \brief Load either the vertex or fragment shader from a custom stream
    ///
    /// This function loads a single shader, either vertex or
    /// fragment, identified by the second argument.
    /// The source code must be a valid shader in GLSL language.
    /// GLSL is a C-like language dedicated to OpenGL shaders;
    /// you'll probably need to read a good documentation for it
    /// before writing your own shaders.
    ///
    /// \param stream Source stream to read from
    /// \param type   Type of shader (vertex or fragment)
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    /// \see loadFromFile, loadFromMemory
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromStream(InputStream& stream, Type type);

    ////////////////////////////////////////////////////////////
    /// \brief Load both the vertex and fragment shaders from custom streams
    ///
    /// This function loads both the vertex and the fragment
    /// shaders. If one of them fails to load, the shader is left
    /// empty (the valid shader is unloaded).
    /// The source codes must be valid shaders in GLSL language.
    /// GLSL is a C-like language dedicated to OpenGL shaders;
    /// you'll probably need to read a good documentation for
    /// it before writing your own shaders.
    ///
    /// \param vertexShaderStream   Source stream to read the vertex shader from
    /// \param fragmentShaderStream Source stream to read the fragment shader from
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    /// \see loadFromFile, loadFromMemory
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromStream(InputStream& vertexShaderStream, InputStream& fragmentShaderStream);

    ////////////////////////////////////////////////////////////
    /// \brief Change a float parameter of the shader
    ///
    /// \a name is the name of the variable to change in the shader.
    /// The corresponding parameter in the shader must be a float
    /// (float GLSL type).
    ///
    /// Example:
    /// \code
    /// uniform float myparam; // this is the variable in the shader
    /// \endcode
    /// \code
    /// shader.setParameter("myparam", 5.2f);
    /// \endcode
    ///
    /// \param name Name of the parameter in the shader
    /// \param x    Value to assign
    ///
    ////////////////////////////////////////////////////////////
    void setParameter(const std::string& name, float x);

    ////////////////////////////////////////////////////////////
    /// \brief Change a 2-components vector parameter of the shader
    ///
    /// \a name is the name of the variable to change in the shader.
    /// The corresponding parameter in the shader must be a 2x1 vector
    /// (vec2 GLSL type).
    ///
    /// Example:
    /// \code
    /// uniform vec2 myparam; // this is the variable in the shader
    /// \endcode
    /// \code
    /// shader.setParameter("myparam", 5.2f, 6.0f);
    /// \endcode
    ///
    /// \param name Name of the parameter in the shader
    /// \param x    First component of the value to assign
    /// \param y    Second component of the value to assign
    ///
    ////////////////////////////////////////////////////////////
    void setParameter(const std::string& name, float x, float y);

    ////////////////////////////////////////////////////////////
    /// \brief Change a 3-components vector parameter of the shader
    ///
    /// \a name is the name of the variable to change in the shader.
    /// The corresponding parameter in the shader must be a 3x1 vector
    /// (vec3 GLSL type).
    ///
    /// Example:
    /// \code
    /// uniform vec3 myparam; // this is the variable in the shader
    /// \endcode
    /// \code
    /// shader.setParameter("myparam", 5.2f, 6.0f, -8.1f);
    /// \endcode
    ///
    /// \param name Name of the parameter in the shader
    /// \param x    First component of the value to assign
    /// \param y    Second component of the value to assign
    /// \param z    Third component of the value to assign
    ///
    ////////////////////////////////////////////////////////////
    void setParameter(const std::string& name, float x, float y, float z);

    ////////////////////////////////////////////////////////////
    /// \brief Change a 4-components vector parameter of the shader
    ///
    /// \a name is the name of the variable to change in the shader.
    /// The corresponding parameter in the shader must be a 4x1 vector
    /// (vec4 GLSL type).
    ///
    /// Example:
    /// \code
    /// uniform vec4 myparam; // this is the variable in the shader
    /// \endcode
    /// \code
    /// shader.setParameter("myparam", 5.2f, 6.0f, -8.1f, 0.4f);
    /// \endcode
    ///
    /// \param name Name of the parameter in the shader
    /// \param x    First component of the value to assign
    /// \param y    Second component of the value to assign
    /// \param z    Third component of the value to assign
    /// \param w    Fourth component of the value to assign
    ///
    ////////////////////////////////////////////////////////////
    void setParameter(const std::string& name, float x, float y, float z, float w);

    ////////////////////////////////////////////////////////////
    /// \brief Change a 2-components vector parameter of the shader
    ///
    /// \a name is the name of the variable to change in the shader.
    /// The corresponding parameter in the shader must be a 2x1 vector
    /// (vec2 GLSL type).
    ///
    /// Example:
    /// \code
    /// uniform vec2 myparam; // this is the variable in the shader
    /// \endcode
    /// \code
    /// shader.setParameter("myparam", cpp3ds::Vector2f(5.2f, 6.0f));
    /// \endcode
    ///
    /// \param name   Name of the parameter in the shader
    /// \param vector Vector to assign
    ///
    ////////////////////////////////////////////////////////////
    void setParameter(const std::string& name, const Vector2f& vector);

    ////////////////////////////////////////////////////////////
    /// \brief Change a 3-components vector parameter of the shader
    ///
    /// \a name is the name of the variable to change in the shader.
    /// The corresponding parameter in the shader must be a 3x1 vector
    /// (vec3 GLSL type).
    ///
    /// Example:
    /// \code
    /// uniform vec3 myparam; // this is the variable in the shader
    /// \endcode
    /// \code
    /// shader.setParameter("myparam", cpp3ds::Vector3f(5.2f, 6.0f, -8.1f));
    /// \endcode
    ///
    /// \param name   Name of the parameter in the shader
    /// \param vector Vector to assign
    ///
    ////////////////////////////////////////////////////////////
    void setParameter(const std::string& name, const Vector3f& vector);

    ////////////////////////////////////////////////////////////
    /// \brief Change a color parameter of the shader
    ///
    /// \a name is the name of the variable to change in the shader.
    /// The corresponding parameter in the shader must be a 4x1 vector
    /// (vec4 GLSL type).
    ///
    /// It is important to note that the components of the color are
    /// normalized before being passed to the shader. Therefore,
    /// they are converted from range [0 .. 255] to range [0 .. 1].
    /// For example, a cpp3ds::Color(255, 125, 0, 255) will be transformed
    /// to a vec4(1.0, 0.5, 0.0, 1.0) in the shader.
    ///
    /// Example:
    /// \code
    /// uniform vec4 color; // this is the variable in the shader
    /// \endcode
    /// \code
    /// shader.setParameter("color", cpp3ds::Color(255, 128, 0, 255));
    /// \endcode
    ///
    /// \param name  Name of the parameter in the shader
    /// \param color Color to assign
    ///
    ////////////////////////////////////////////////////////////
    void setParameter(const std::string& name, const Color& color);

    ////////////////////////////////////////////////////////////
    /// \brief Change a matrix parameter of the shader
    ///
    /// \a name is the name of the variable to change in the shader.
    /// The corresponding parameter in the shader must be a 4x4 matrix
    /// (mat4 GLSL type).
    ///
    /// Example:
    /// \code
    /// uniform mat4 matrix; // this is the variable in the shader
    /// \endcode
    /// \code
    /// cpp3ds::Transform transform;
    /// transform.translate(5, 10);
    /// shader.setParameter("matrix", transform);
    /// \endcode
    ///
    /// \param name      Name of the parameter in the shader
    /// \param transform Transform to assign
    ///
    ////////////////////////////////////////////////////////////
    void setParameter(const std::string& name, const cpp3ds::Transform& transform);

    ////////////////////////////////////////////////////////////
    /// \brief Change a texture parameter of the shader
    ///
    /// \a name is the name of the variable to change in the shader.
    /// The corresponding parameter in the shader must be a 2D texture
    /// (sampler2D GLSL type).
    ///
    /// Example:
    /// \code
    /// uniform sampler2D the_texture; // this is the variable in the shader
    /// \endcode
    /// \code
    /// cpp3ds::Texture texture;
    /// ...
    /// shader.setParameter("the_texture", texture);
    /// \endcode
    /// It is important to note that \a texture must remain alive as long
    /// as the shader uses it, no copy is made internally.
    ///
    /// To use the texture of the object being draw, which cannot be
    /// known in advance, you can pass the special value
    /// cpp3ds::Shader::CurrentTexture:
    /// \code
    /// shader.setParameter("the_texture", cpp3ds::Shader::CurrentTexture).
    /// \endcode
    ///
    /// \param name    Name of the texture in the shader
    /// \param texture Texture to assign
    ///
    ////////////////////////////////////////////////////////////
    void setParameter(const std::string& name, const Texture& texture);

    ////////////////////////////////////////////////////////////
    /// \brief Change a texture parameter of the shader
    ///
    /// This overload maps a shader texture variable to the
    /// texture of the object being drawn, which cannot be
    /// known in advance. The second argument must be
    /// cpp3ds::Shader::CurrentTexture.
    /// The corresponding parameter in the shader must be a 2D texture
    /// (sampler2D GLSL type).
    ///
    /// Example:
    /// \code
    /// uniform sampler2D current; // this is the variable in the shader
    /// \endcode
    /// \code
    /// shader.setParameter("current", cpp3ds::Shader::CurrentTexture);
    /// \endcode
    ///
    /// \param name Name of the texture in the shader
    ///
    ////////////////////////////////////////////////////////////
    void setParameter(const std::string& name, CurrentTextureType);

    ////////////////////////////////////////////////////////////
    /// \brief Get the underlying OpenGL handle of the shader.
    ///
    /// You shouldn't need to use this function, unless you have
    /// very specific stuff to implement that cpp3ds doesn't support,
    /// or implement a temporary workaround until a bug is fixed.
    ///
    /// \return OpenGL handle of the shader or 0 if not yet loaded
    ///
    ////////////////////////////////////////////////////////////
    unsigned int getNativeHandle() const;

    ////////////////////////////////////////////////////////////
    /// \brief Bind a shader for rendering
    ///
    /// This function is not part of the graphics API, it mustn't be
    /// used when drawing cpp3ds entities. It must be used only if you
    /// mix cpp3ds::Shader with OpenGL code.
    ///
    /// \code
    /// cpp3ds::Shader s1, s2;
    /// ...
    /// cpp3ds::Shader::bind(&s1);
    /// // draw OpenGL stuff that use s1...
    /// cpp3ds::Shader::bind(&s2);
    /// // draw OpenGL stuff that use s2...
    /// cpp3ds::Shader::bind(NULL);
    /// // draw OpenGL stuff that use no shader...
    /// \endcode
    ///
    /// \param shader Shader to bind, can be null to use no shader
    ///
    ////////////////////////////////////////////////////////////
    static void bind(const Shader* shader);

    ////////////////////////////////////////////////////////////
    /// \brief Tell whether or not the system supports shaders
    ///
    /// This function should always be called before using
    /// the shader features. If it returns false, then
    /// any attempt to use cpp3ds::Shader will fail.
    ///
    /// \return True if shaders are supported, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    static bool isAvailable();

private :

    ////////////////////////////////////////////////////////////
    /// \brief Compile the shader(s) and create the program
    ///
    /// If one of the arguments is NULL, the corresponding shader
    /// is not created.
    ///
    /// \param vertexShaderCode   Source code of the vertex shader
    /// \param fragmentShaderCode Source code of the fragment shader
    ///
    /// \return True on success, false if any error happened
    ///
    ////////////////////////////////////////////////////////////
    bool compile(const char* vertexShaderCode, const char* fragmentShaderCode);

    bool loadProgram(const Uint8* data, const Uint32 size);

    ////////////////////////////////////////////////////////////
    /// \brief Bind all the textures used by the shader
    ///
    /// This function each texture to a different unit, and
    /// updates the corresponding variables in the shader accordingly.
    ///
    ////////////////////////////////////////////////////////////
    void bindTextures() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the location ID of a shader parameter
    ///
    /// \param name Name of the parameter to search
    ///
    /// \return Location ID of the parameter, or -1 if not found
    ///
    ////////////////////////////////////////////////////////////
    int getParamLocation(const std::string& name);

    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::map<int, const Texture*> TextureTable;
    typedef std::map<std::string, int> ParamTable;

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    GLuint       m_shaderProgram;  ///< OpenGL identifier for the program
    int          m_currentTexture; ///< Location of the current texture in the shader
    TextureTable m_textures;       ///< Texture variables in the shader, mapped to their location
    ParamTable   m_params;         ///< Parameters location cache

    #ifndef EMULATION
    //shader structure
    DVLB_s* dvlb;
    shaderProgram_s shader;
    #endif
};

}


#endif


////////////////////////////////////////////////////////////
/// \class cpp3ds::Shader
/// \ingroup graphics
///
/// Shaders are programs written using a specific language,
/// executed directly by the graphics card and allowing
/// to apply real-time operations to the rendered entities.
///
/// There are two kinds of shaders:
/// \li Vertex shaders, that process vertices
/// \li Fragment (pixel) shaders, that process pixels
///
/// A cpp3ds::Shader can be composed of either a vertex shader
/// alone, a fragment shader alone, or both combined
/// (see the variants of the load functions).
///
/// Shaders are written in GLSL, which is a C-like
/// language dedicated to OpenGL shaders. You'll probably
/// need to learn its basics before writing your own shaders
/// for cpp3ds.
///
/// Like any C/C++ program, a shader has its own variables
/// that you can set from your C++ application. cpp3ds::Shader
/// handles 5 different types of variables:
/// \li floats
/// \li vectors (2, 3 or 4 components)
/// \li colors
/// \li textures
/// \li transforms (matrices)
///
/// The value of the variables can be changed at any time
/// with the various overloads of the setParameter function:
/// \code
/// shader.setParameter("offset", 2.f);
/// shader.setParameter("point", 0.5f, 0.8f, 0.3f);
/// shader.setParameter("color", cpp3ds::Color(128, 50, 255));
/// shader.setParameter("matrix", transform); // transform is a cpp3ds::Transform
/// shader.setParameter("overlay", texture); // texture is a cpp3ds::Texture
/// shader.setParameter("texture", cpp3ds::Shader::CurrentTexture);
/// \endcode
///
/// The special Shader::CurrentTexture argument maps the
/// given texture variable to the current texture of the
/// object being drawn (which cannot be known in advance).
///
/// To apply a shader to a drawable, you must pass it as an
/// additional parameter to the Draw function:
/// \code
/// window.draw(sprite, &shader);
/// \endcode
///
/// ... which is in fact just a shortcut for this:
/// \code
/// cpp3ds::RenderStates states;
/// states.shader = &shader;
/// window.draw(sprite, states);
/// \endcode
///
/// In the code above we pass a pointer to the shader, because it may
/// be null (which means "no shader").
///
/// Shaders can be used on any drawable, but some combinations are
/// not interesting. For example, using a vertex shader on a cpp3ds::Sprite
/// is limited because there are only 4 vertices, the sprite would
/// have to be subdivided in order to apply wave effects.
/// Another bad example is a fragment shader with cpp3ds::Text: the texture
/// of the text is not the actual text that you see on screen, it is
/// a big texture containing all the characters of the font in an
/// arbitrary order; thus, texture lookups on pixels other than the
/// current one may not give you the expected result.
///
/// Shaders can also be used to apply global post-effects to the
/// current contents of the target. This can be done in two different ways:
/// \li draw everything to a cpp3ds::RenderTexture, then draw it to
///     the main target using the shader
/// \li draw everything directly to the main target, then use
///     cpp3ds::Texture::update(Window&) to copy its contents to a texture
///     and draw it to the main target using the shader
///
/// The first technique is more optimized because it doesn't involve
/// retrieving the target's pixels to system memory, but the
/// second one doesn't impact the rendering process and can be
/// easily inserted anywhere without impacting all the code.
///
/// Like cpp3ds::Texture that can be used as a raw OpenGL texture,
/// cpp3ds::Shader can also be used directly as a raw shader for
/// custom OpenGL geometry.
/// \code
/// cpp3ds::Shader::bind(&shader);
/// ... render OpenGL geometry ...
/// cpp3ds::Shader::bind(NULL);
/// \endcode
///
////////////////////////////////////////////////////////////