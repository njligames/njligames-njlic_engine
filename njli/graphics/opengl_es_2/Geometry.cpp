//
//  Geometry.cpp
//  NJLICGames
//
//  Created by James Folk on 12/8/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#include "Geometry.h"
#include "GraphicsPlatform.h"

#include <assert.h>
#include <iostream>

#include "Camera.h"
#include "Node.h"
#include "ShaderProgram.h"

#include "World.h"

#include "Log.h"
#define TAG "Cube.cpp"
#define FORMATSTRING "{\"njli::MeshGeometry\":[]}"
#include "JsonJLI.h"
#include "btPrint.h"

#include "Image.h"
#include "Material.h"

namespace njli
{
  Geometry::Geometry()
      : AbstractFactoryObject(this), m_MatrixBuffer(new GLfloat[16]),
        m_MatrixBufferFullSize(new float[16]), m_ModelViewTransformData(NULL),
        m_NormalMatrixTransformData(NULL), m_VertexArray(0),
        m_ModelViewBuffer(0), m_NormalMatrixTransformBuffer(0),
        m_VerticesBuffer(0), m_IndexBuffer(0), m_NumberInstances(1),
        m_NumberSubDivisions(1), m_ExtraSubdivisionBuffer(1), m_Shader(NULL),
        m_OpacityModifyRGB(false), m_ElementBufferChanged(true),
        m_VertexBufferChanged(true), m_NormalMatrixBufferChanged(true),
        m_ModelViewBufferChanged(true), m_ShaderChanged(true),

        m_RimLightColor(0.1f, 0.1f, 0.1f), m_RimLightStart(0.0f),
        m_RimLightEnd(1.0f), m_RimLightCoefficient(0.6f),
        m_LightSourceAmbientColor(1.0f, 1.0f, 1.0f),
        m_LightSourceDiffuseColor(1.0f, 1.0f, 1.0f),
        m_LightSourceSpecularColor(0.0f, 0.0f, 0.0f),
        m_LightSourcePosition_worldspace(0.0f, 0.0f, -1.0f, 1.0f),
        m_LightSourceSpotDirection(0.0f, 0.0f, 1.0f),
        m_LightSourceSpotExponent(100.0f), m_LightSourceSpotCutoff(180.0f),
        m_LightSourceSpotCosCutoff(30.0f),
        m_LightSourceConstantAttenuation(1.0f),
        m_LightSourceLinearAttenuation(0.045f),
        m_LightSourceQuadraticAttenuation(0.0075f),
        m_LightAmbientColor(1.0f, 1.0f, 1.0f), m_MaterialShininess(1000.0f),
        m_FogMaxDistance(11.0f), m_FogMinDistance(5.0f),
        m_FogColor(1.0f, 1.0f, 1.0f),
        m_FogDensity(std::numeric_limits<float>::denorm_min()),
        m_blendFuncSource(GL_SRC_ALPHA),
        m_blendFuncDestination(GL_ONE_MINUS_SRC_ALPHA), m_enableBlend(true),
        m_enableDepthTest(true), m_enableStencilTest(false), m_Material(NULL),
        m_RenderCategory(JLI_BIT_CATEGORY_NONE)
  {
    assert(m_MatrixBuffer);
    assert(m_MatrixBufferFullSize);

    m_References.resize(m_NumberInstances);
  }

  Geometry::Geometry(const AbstractBuilder &builder)
      : AbstractFactoryObject(this), m_MatrixBuffer(new GLfloat[16]),
        m_MatrixBufferFullSize(new float[16]), m_ModelViewTransformData(NULL),
        m_NormalMatrixTransformData(NULL), m_VertexArray(0),
        m_ModelViewBuffer(0), m_NormalMatrixTransformBuffer(0),
        m_VerticesBuffer(0), m_IndexBuffer(0), m_NumberInstances(1),
        m_NumberSubDivisions(1), m_ExtraSubdivisionBuffer(1), m_Shader(NULL),
        m_OpacityModifyRGB(false), m_ElementBufferChanged(true),
        m_VertexBufferChanged(true), m_NormalMatrixBufferChanged(true),
        m_ModelViewBufferChanged(true), m_ShaderChanged(true),

        m_RimLightColor(0.1f, 0.1f, 0.1f), m_RimLightStart(0.0f),
        m_RimLightEnd(1.0f), m_RimLightCoefficient(0.6f),
        m_LightSourceAmbientColor(1.0f, 1.0f, 1.0f),
        m_LightSourceDiffuseColor(1.0f, 1.0f, 1.0f),
        m_LightSourceSpecularColor(0.0f, 0.0f, 0.0f),
        m_LightSourcePosition_worldspace(0.0f, 0.0f, -1.0f, 1.0f),
        m_LightSourceSpotDirection(0.0f, 0.0f, 1.0f),
        m_LightSourceSpotExponent(100.0f), m_LightSourceSpotCutoff(180.0f),
        m_LightSourceSpotCosCutoff(30.0f),
        m_LightSourceConstantAttenuation(1.0f),
        m_LightSourceLinearAttenuation(0.045f),
        m_LightSourceQuadraticAttenuation(0.0075f),
        m_LightAmbientColor(1.0f, 1.0f, 1.0f), m_MaterialShininess(1000.0f),
        m_FogMaxDistance(11.0f), m_FogMinDistance(5.0f),
        m_FogColor(1.0f, 1.0f, 1.0f),
        m_FogDensity(std::numeric_limits<float>::denorm_min()),
        m_blendFuncSource(GL_SRC_ALPHA),
        m_blendFuncDestination(GL_ONE_MINUS_SRC_ALPHA), m_enableBlend(true),
        m_enableDepthTest(true), m_enableStencilTest(false), m_Material(NULL),
        m_RenderCategory(JLI_BIT_CATEGORY_NONE)
  {
    assert(m_MatrixBuffer);
    assert(m_MatrixBufferFullSize);

    m_References.resize(m_NumberInstances);
  }

  Geometry::Geometry(const Geometry &copy)
      : AbstractFactoryObject(this), m_MatrixBuffer(new GLfloat[16]),
        m_MatrixBufferFullSize(new float[16]), m_ModelViewTransformData(NULL),
        m_NormalMatrixTransformData(NULL), m_VertexArray(0),
        m_ModelViewBuffer(0), m_NormalMatrixTransformBuffer(0),
        m_VerticesBuffer(0), m_IndexBuffer(0), m_NumberInstances(1),
        m_NumberSubDivisions(1), m_ExtraSubdivisionBuffer(1), m_Shader(NULL),
        m_OpacityModifyRGB(false), m_ElementBufferChanged(true),
        m_VertexBufferChanged(true), m_NormalMatrixBufferChanged(true),
        m_ModelViewBufferChanged(true), m_ShaderChanged(true),

        m_RimLightColor(0.1f, 0.1f, 0.1f), m_RimLightStart(0.0f),
        m_RimLightEnd(1.0f), m_RimLightCoefficient(0.6f),
        m_LightSourceAmbientColor(1.0f, 1.0f, 1.0f),
        m_LightSourceDiffuseColor(1.0f, 1.0f, 1.0f),
        m_LightSourceSpecularColor(0.0f, 0.0f, 0.0f),
        m_LightSourcePosition_worldspace(0.0f, 0.0f, -1.0f, 1.0f),
        m_LightSourceSpotDirection(0.0f, 0.0f, 1.0f),
        m_LightSourceSpotExponent(100.0f), m_LightSourceSpotCutoff(180.0f),
        m_LightSourceSpotCosCutoff(30.0f),
        m_LightSourceConstantAttenuation(1.0f),
        m_LightSourceLinearAttenuation(0.045f),
        m_LightSourceQuadraticAttenuation(0.0075f),
        m_LightAmbientColor(1.0f, 1.0f, 1.0f), m_MaterialShininess(1000.0f),
        m_FogMaxDistance(11.0f), m_FogMinDistance(5.0f),
        m_FogColor(1.0f, 1.0f, 1.0f),
        m_FogDensity(std::numeric_limits<float>::denorm_min()),
        m_blendFuncSource(GL_SRC_ALPHA),
        m_blendFuncDestination(GL_ONE_MINUS_SRC_ALPHA), m_enableBlend(true),
        m_enableDepthTest(true), m_enableStencilTest(false), m_Material(NULL),
        m_RenderCategory(JLI_BIT_CATEGORY_NONE)
  {
    assert(m_MatrixBuffer);
    assert(m_MatrixBufferFullSize);

    m_References.resize(m_NumberInstances);
  }

  Geometry::~Geometry()
  {
    if (m_NormalMatrixTransformData)
      delete[] m_NormalMatrixTransformData;
    m_NormalMatrixTransformData = NULL;

    if (m_ModelViewTransformData)
      delete[] m_ModelViewTransformData;
    m_ModelViewTransformData = NULL;

    delete[] m_MatrixBufferFullSize;
    m_MatrixBufferFullSize = NULL;

    delete[] m_MatrixBuffer;
    m_MatrixBuffer = NULL;
  }

  //    Geometry::Geometry()
  //    : AbstractFactoryObject(this),
  //    //    m_Name("MyGeometry"),
  //    m_Material(NULL), m_ShaderProgram(NULL), m_projectionMatrixUniform(-1),
  //    //    m_modelViewMatrixUniform(-1),
  //    m_ModelviewTransform(NULL), m_ColorTransform(NULL),
  //    m_modelViewBufferID(-1), m_colorTransformBufferID(-1),
  //    m_InTransformAttrib(-1), m_InColorTransform(-1),
  //    //    m_CurrentMeshCount(-1),
  //    m_verticesBufferID(-1), indexBufferID(-1), m_vertexArrayID(-1),
  //    m_InPositionAttrib(-1), m_InTexCoordAttrib(-1), m_InColorAttrib(-1),
  //    m_blendFuncSource(GL_SRC_ALPHA),
  //    m_blendFuncDestination(GL_ONE_MINUS_SRC_ALPHA),
  //    _opacityModifyRGB(false), m_enableBlend(true), m_enableDepthTest(true),
  //    m_enableStencilTest(false), m_TransformDirty(true),
  //    m_ColorTransformDirty(true),
  //    //    m_StartCopyTransform(std::numeric_limits<u64>::max()),
  //    m_LoadGPU(false), m_setupOpacity_Material(NULL),
  //    m_setupOpacity_Image(NULL), m_setupOpacity(false), m_UnLoadGPU(false),
  //    //    m_setupShader(false),
  //    m_bufferModified(true), m_vertexAttribChanged(false),
  //    m_MatrixBuffer(new float[16]), m_maxindice(0),
  //    m_RenderCategory(JLI_BIT_CATEGORY_NONE)
  //    {
  //        enableRenderObject();
  //    }
  //
  //    Geometry::Geometry(const AbstractBuilder &builder)
  //    : AbstractFactoryObject(this),
  //    //    m_Name("MyGeometry"),
  //    m_Material(NULL), m_ShaderProgram(NULL), m_projectionMatrixUniform(-1),
  //    //    m_modelViewMatrixUniform(-1),
  //    m_ModelviewTransform(NULL), m_ColorTransform(NULL),
  //    m_modelViewBufferID(-1), m_colorTransformBufferID(-1),
  //    m_InTransformAttrib(-1), m_InColorTransform(-1),
  //    //    m_CurrentMeshCount(-1),
  //    m_verticesBufferID(-1), indexBufferID(-1), m_vertexArrayID(-1),
  //    m_InPositionAttrib(-1), m_InTexCoordAttrib(-1), m_InColorAttrib(-1),
  //    m_blendFuncSource(GL_SRC_ALPHA),
  //    m_blendFuncDestination(GL_ONE_MINUS_SRC_ALPHA),
  //    _opacityModifyRGB(false), m_enableBlend(true), m_enableDepthTest(true),
  //    m_enableStencilTest(false), m_TransformDirty(true),
  //    m_ColorTransformDirty(true),
  //    //    m_StartCopyTransform(std::numeric_limits<u64>::max()),
  //    m_LoadGPU(false), m_setupOpacity_Material(NULL),
  //    m_setupOpacity_Image(NULL), m_setupOpacity(false), m_UnLoadGPU(false),
  //    //    m_setupShader(false),
  //    m_bufferModified(true), m_vertexAttribChanged(false),
  //    m_MatrixBuffer(new float[16]), m_maxindice(0),
  //    m_RenderCategory(JLI_BIT_CATEGORY_NONE)
  //    {
  //        enableRenderObject();
  //    }
  //
  //    Geometry::Geometry(const Geometry &copy)
  //    : AbstractFactoryObject(this),
  //    //    m_Name("MyGeometry"),
  //    m_Material(NULL), m_ShaderProgram(NULL), m_projectionMatrixUniform(-1),
  //    //    m_modelViewMatrixUniform(-1),
  //    m_ModelviewTransform(NULL), m_ColorTransform(NULL),
  //    m_modelViewBufferID(-1), m_colorTransformBufferID(-1),
  //    m_InTransformAttrib(-1), m_InColorTransform(-1),
  //    //    m_CurrentMeshCount(-1),
  //    m_verticesBufferID(-1), indexBufferID(-1), m_vertexArrayID(-1),
  //    m_InPositionAttrib(-1), m_InTexCoordAttrib(-1), m_InColorAttrib(-1),
  //    m_InOpacityAttrib(-1), m_InHiddenAttrib(-1),
  //    m_blendFuncSource(GL_SRC_ALPHA),
  //    m_blendFuncDestination(GL_ONE_MINUS_SRC_ALPHA),
  //    _opacityModifyRGB(false), m_enableBlend(true), m_enableDepthTest(true),
  //    m_enableStencilTest(false), m_TransformDirty(true),
  //    m_ColorTransformDirty(true),
  //    //    m_StartCopyTransform(std::numeric_limits<u64>::max()),
  //    m_LoadGPU(false), m_setupOpacity_Material(NULL),
  //    m_setupOpacity_Image(NULL), m_setupOpacity(false), m_UnLoadGPU(false),
  //    //    m_setupShader(false),
  //    m_bufferModified(true), m_vertexAttribChanged(false),
  //    m_MatrixBuffer(new float[16]), m_maxindice(0),
  //    m_RenderCategory(JLI_BIT_CATEGORY_NONE)
  //    {
  //        enableRenderObject();
  //    }
  //
  //    Geometry::~Geometry()
  //    {
  //        delete[] m_MatrixBuffer;
  //        m_MatrixBuffer = NULL;
  //
  //        unLoadGPU_Internal();
  //    }

  Geometry &Geometry::operator=(const Geometry &rhs)
  {
    if (this != &rhs)
      {
      }
    return *this;
  }

  s32 Geometry::calculateSerializeBufferSize() const
  {
    // TODO: calculateSerializeBufferSize
    return 0;
  }

  void Geometry::serialize(void *dataBuffer, btSerializer *serializer) const
  {
    // TODO: serialize
  }

  const char *Geometry::getClassName() const { return "Geometry"; }

  s32 Geometry::getType() const { return Geometry::type(); }

  Geometry::operator std::string() const
  {
    return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
  }

  Geometry *Geometry::create(u32 type)
  {
    SDL_assert(type == JLI_OBJECT_TYPE_Plane);

    return dynamic_cast<Geometry *>(
        World::getInstance()->getWorldFactory()->create(type));
  }

  void Geometry::destroy(Geometry *object)
  {
    if (object)
      {
        //            object->removeMaterial();
        //            object->removeShaderProgram();
        //            object->removeAllLevelOfDetails();

        World::getInstance()->getWorldFactory()->destroy(object);
      }
  }

  void Geometry::load(Geometry &object, lua_State *L, int index)
  {
    // Push another reference to the table on top of the stack (so we know
    // where it is, and this function can work for negative, positive and
    // pseudo indices
    lua_pushvalue(L, index);
    // stack now contains: -1 => table
    lua_pushnil(L);
    // stack now contains: -1 => nil; -2 => table
    while (lua_next(L, -2))
      {
        // stack now contains: -1 => value; -2 => key; -3 => table
        // copy the key so that lua_tostring does not modify the original
        lua_pushvalue(L, -2);
        // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
        const char *key = lua_tostring(L, -1);
        //            const char *value = lua_tostring(L, -2);
        if (lua_istable(L, -2))
          {
            Geometry::load(object, L, -2);
          }
        else
          {
            if (lua_isnumber(L, index))
              {
                double number = lua_tonumber(L, index);
                printf("%s => %f\n", key, number);
              }
            else if (lua_isstring(L, index))
              {
                const char *v = lua_tostring(L, index);
                printf("%s => %s\n", key, v);
              }
            else if (lua_isboolean(L, index))
              {
                bool v = lua_toboolean(L, index);
                printf("%s => %d\n", key, v);
              }
            else if (lua_isuserdata(L, index))
              {
                //                    swig_lua_userdata *usr;
                //                    swig_type_info *type;
                //                    assert(lua_isuserdata(L,index));
                //                    usr=(swig_lua_userdata*)lua_touserdata(L,index);
                //                    /* get data */
                //                    type = usr->type;
                //                    njli::AbstractFactoryObject *object =
                //                    static_cast<njli::AbstractFactoryObject*>(usr->ptr);
                //                    printf("%s => %d:%s\n", key,
                //                    object->getType(),
                //                    object->getClassName());
              }
          }
        // pop value + copy of key, leaving original key
        lua_pop(L, 2);
        // stack now contains: -1 => key; -2 => table
      }
    // stack now contains: -1 => table (when lua_next returns 0 it pops the key
    // but does not push anything.)
    // Pop table
    lua_pop(L, 1);
    // Stack is now the same as it was on entry to this function
  }

  u32 Geometry::type() { return JLI_OBJECT_TYPE_Geometry; }

  void Geometry::setBlendSource(s32 source) { m_blendFuncSource = source; }

  void Geometry::setBlendDestination(s32 dest)
  {
    m_blendFuncDestination = dest;
  }

  void Geometry::enableBlend(const bool enable) { m_enableBlend = enable; }

  void Geometry::enableDepthTest(const bool enable)
  {
    m_enableDepthTest = enable;
  }

  void Geometry::enableStencilTest(const bool enable)
  {
    m_enableStencilTest = enable;
  }

  //    Geometry::Geometry():
  //    m_MatrixBuffer(new GLfloat[16]),
  //    m_MatrixBufferFullSize(new float[16]),
  //    m_ModelViewTransformData(NULL),
  //    m_NormalMatrixTransformData(NULL),
  //    m_VertexArray(0),
  //    m_ModelViewBuffer(0),
  //    m_NormalMatrixTransformBuffer(0),
  //    m_VerticesBuffer(0),
  //    m_IndexBuffer(0),
  //    m_NumberInstances(1),
  //    m_NumberSubDivisions(1),
  //    m_ExtraSubdivisionBuffer(1),
  //    m_Shader(NULL),
  //    m_OpacityModifyRGB(false),
  //    m_ElementBufferChanged(true),
  //    m_VertexBufferChanged(true),
  //    m_NormalMatrixBufferChanged(true),
  //    m_ModelViewBufferChanged(true),
  //    m_ShaderChanged(true),
  //
  //    m_RimLightColor(0.1f, 0.1f, 0.1f),
  //    m_RimLightStart(0.0f),
  //    m_RimLightEnd(1.0f),
  //    m_RimLightCoefficient(0.6f),
  //    m_LightSourceAmbientColor(1.0f, 1.0f, 1.0f),
  //    m_LightSourceDiffuseColor(1.0f, 1.0f, 1.0f),
  //    m_LightSourceSpecularColor(0.0f, 0.0f, 1.0f),
  //    m_LightSourcePosition_worldspace(0.0f, 0.0f, -1.0f, 1.0f),
  //    m_LightSourceSpotDirection(0.0f, 0.0f, 1.0f),
  //    m_LightSourceSpotExponent(100.0f),
  //    m_LightSourceSpotCutoff(180.0f),
  //    m_LightSourceSpotCosCutoff(30.0f),
  //    m_LightSourceConstantAttenuation(1.0f),
  //    m_LightSourceLinearAttenuation(0.045f),
  //    m_LightSourceQuadraticAttenuation(0.0075f),
  //    m_LightAmbientColor(1.0f, 1.0f, 1.0f),
  //    m_MaterialShininess(1000.0f),
  //    m_FogMaxDistance(11.0f),
  //    m_FogMinDistance(5.0f),
  //    m_FogColor(1.0f, 1.0f, 1.0f),
  //    m_FogDensity(0.1f)
  //    {
  //        assert(m_MatrixBuffer);
  //        assert(m_MatrixBufferFullSize);
  //
  //        m_References.resize(m_NumberInstances);
  //    }
  //
  //
  //    Geometry::~Geometry()
  //    {
  //        if(m_NormalMatrixTransformData)
  //            delete [] m_NormalMatrixTransformData;
  //        m_NormalMatrixTransformData = NULL;
  //
  //        if(m_ModelViewTransformData)
  //            delete [] m_ModelViewTransformData;
  //        m_ModelViewTransformData = NULL;
  //
  //        delete [] m_MatrixBufferFullSize;
  //        m_MatrixBufferFullSize = NULL;
  //
  //        delete [] m_MatrixBuffer;
  //        m_MatrixBuffer = NULL;
  //    }

  void Geometry::load(ShaderProgram *shader, const std::string &filecontent,
                      unsigned int numInstances, unsigned int numSubDivisions)
  {
    assert(shader);

    setShaderProgram(shader);

    m_NumberInstances = numInstances;
    m_NumberSubDivisions = numSubDivisions;
    for (int i = 0; i < m_NumberSubDivisions; i++)
      m_ExtraSubdivisionBuffer *= 4;

    m_References.resize(m_NumberInstances);

    loadData();

    assert(m_VertexArray == 0);

    glGenVertexArrays_NJLIC(1, &m_VertexArray);
    glBindVertexArray_NJLIC(m_VertexArray);
    {
      {
        assert(m_ModelViewBuffer == 0);
        glGenBuffers(1, &m_ModelViewBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_ModelViewBuffer);
        glBufferData(GL_ARRAY_BUFFER,
                     getModelViewTransformArrayBufferSize() *
                         subdivisionBufferSize(),
                     getModelViewTransformArrayBufferPtr(), GL_STREAM_DRAW);
        int inTransformAttrib =
            getShader()->getAttributeLocation("inTransform");
        glEnableVertexAttribArray(inTransformAttrib + 0);
        glEnableVertexAttribArray(inTransformAttrib + 1);
        glEnableVertexAttribArray(inTransformAttrib + 2);
        glEnableVertexAttribArray(inTransformAttrib + 3);
        glVertexAttribPointer(inTransformAttrib + 0, 4, GL_FLOAT, 0,
                              sizeof(GLfloat) * 16, (GLvoid *)0);
        glVertexAttribPointer(inTransformAttrib + 1, 4, GL_FLOAT, 0,
                              sizeof(GLfloat) * 16, (GLvoid *)16);
        glVertexAttribPointer(inTransformAttrib + 2, 4, GL_FLOAT, 0,
                              sizeof(GLfloat) * 16, (GLvoid *)32);
        glVertexAttribPointer(inTransformAttrib + 3, 4, GL_FLOAT, 0,
                              sizeof(GLfloat) * 16, (GLvoid *)48);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
      }

      {
        assert(m_NormalMatrixTransformBuffer == 0);
        glGenBuffers(1, &m_NormalMatrixTransformBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_NormalMatrixTransformBuffer);
        glBufferData(GL_ARRAY_BUFFER,
                     getNormalMatrixTransformArrayBufferSize() *
                         subdivisionBufferSize(),
                     getNormalMatrixTransformArrayBufferPtr(), GL_STREAM_DRAW);
        int inNormalMatrixAttrib =
            getShader()->getAttributeLocation("inNormalMatrix");
        glEnableVertexAttribArray(inNormalMatrixAttrib + 0);
        glEnableVertexAttribArray(inNormalMatrixAttrib + 1);
        glEnableVertexAttribArray(inNormalMatrixAttrib + 2);
        glEnableVertexAttribArray(inNormalMatrixAttrib + 3);
        glVertexAttribPointer(inNormalMatrixAttrib + 0, 4, GL_FLOAT, 0,
                              sizeof(GLfloat) * 16, (GLvoid *)0);
        glVertexAttribPointer(inNormalMatrixAttrib + 1, 4, GL_FLOAT, 0,
                              sizeof(GLfloat) * 16, (GLvoid *)16);
        glVertexAttribPointer(inNormalMatrixAttrib + 2, 4, GL_FLOAT, 0,
                              sizeof(GLfloat) * 16, (GLvoid *)32);
        glVertexAttribPointer(inNormalMatrixAttrib + 3, 4, GL_FLOAT, 0,
                              sizeof(GLfloat) * 16, (GLvoid *)48);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
      }

      {
        assert(m_VerticesBuffer == 0);
        glGenBuffers(1, &m_VerticesBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_VerticesBuffer);
        glBufferData(GL_ARRAY_BUFFER,
                     getVertexArrayBufferSize() * subdivisionBufferSize(),
                     getVertexArrayBufferPtr(), GL_STREAM_DRAW);
        int inPositionAttrib = getShader()->getAttributeLocation("inPosition");
        int inColorAttrib = getShader()->getAttributeLocation("inColor");
        int inNormalAttrib = getShader()->getAttributeLocation("inNormal");
        int inTexCoordAttrib = getShader()->getAttributeLocation("inTexCoord");

        int inTangentAttrib = getShader()->getAttributeLocation("inTangent");
        int inBiTangentAttrib =
            getShader()->getAttributeLocation("inBiTangent");

        glEnableVertexAttribArray(inPositionAttrib);
        glVertexAttribPointer(
            inPositionAttrib, 3, GL_FLOAT, GL_FALSE,
            sizeof(TexturedColoredVertex),
            (const GLvoid *)offsetof(TexturedColoredVertex, vertex));

        glEnableVertexAttribArray(inTexCoordAttrib);
        glVertexAttribPointer(
            inTexCoordAttrib, 2, GL_FLOAT, GL_FALSE,
            sizeof(TexturedColoredVertex),
            (const GLvoid *)offsetof(TexturedColoredVertex, texture));

        glEnableVertexAttribArray(inNormalAttrib);
        glVertexAttribPointer(
            inNormalAttrib, 3, GL_FLOAT, GL_FALSE,
            sizeof(TexturedColoredVertex),
            (const GLvoid *)offsetof(TexturedColoredVertex, normal));

        glEnableVertexAttribArray(inColorAttrib);
        glVertexAttribPointer(
            inColorAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(TexturedColoredVertex),
            (const GLvoid *)offsetof(TexturedColoredVertex, color));

        glEnableVertexAttribArray(inTangentAttrib);
        glVertexAttribPointer(
            inTangentAttrib, 3, GL_FLOAT, GL_FALSE,
            sizeof(TexturedColoredVertex),
            (const GLvoid *)offsetof(TexturedColoredVertex, tangent));

        glEnableVertexAttribArray(inBiTangentAttrib);
        glVertexAttribPointer(
            inBiTangentAttrib, 3, GL_FLOAT, GL_FALSE,
            sizeof(TexturedColoredVertex),
            (const GLvoid *)offsetof(TexturedColoredVertex, bitangent));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
      }

      {
        glGenBuffers(1, &m_IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     getElementArrayBufferSize() * subdivisionBufferSize(),
                     getElementArrayBufferPtr(), GL_STREAM_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      }
    }

    glBindVertexArray_NJLIC(0);
  }

  void Geometry::unLoad()
  {
    if (m_IndexBuffer)
      glDeleteBuffers(1, &m_IndexBuffer);
    m_IndexBuffer = 0;

    if (m_VerticesBuffer)
      glDeleteBuffers(1, &m_VerticesBuffer);
    m_VerticesBuffer = 0;

    if (m_NormalMatrixTransformBuffer)
      glDeleteBuffers(1, &m_NormalMatrixTransformBuffer);
    m_NormalMatrixTransformBuffer = 0;

    if (m_ModelViewBuffer)
      glDeleteBuffers(1, &m_ModelViewBuffer);
    m_ModelViewBuffer = 0;

    if (m_VertexArray)
      {

        glDeleteVertexArrays_NJLIC(1, &m_VertexArray);
      }
    m_VertexArray = 0;
  }

  bool Geometry::isLoaded() const { return false; }

  ShaderProgram *const Geometry::getShader() { return m_Shader; }

  void Geometry::setShaderProgram(ShaderProgram *const shader)
  {
    m_Shader = shader;
    m_ShaderChanged = true;
  }

  void Geometry::render(Camera *camera)
  {
    ShaderProgram *shader = getShader();
    if (shader && camera)
      {
        shader->use();
        m_ShaderChanged = true;
        camera->render(shader, m_ShaderChanged);

        struct LightSourceParameters
        {
          btVector4 ambient;
          btVector4 diffuse;
          btVector4 specular;
          btVector4 position;
          btVector4 halfVector;
          btVector3 spotDirection;
          float spotExponent;
          float spotCutoff;
          float spotCosCutoff;
          float constantAttenuation;
          float linearAttenuation;
          float quadraticAttenuation;
        };

        struct MaterialParameters
        {
          btVector4 emission;
          btVector4 ambient;
          btVector4 diffuse;
          btVector4 specular;
          float shininess;
        };

        Material *material = getMaterial();
        if (material)
          {
            material->bind(shader);
          }
        //            glActiveTexture(GL_TEXTURE0 + 0);
        //            glBindTexture(GL_TEXTURE_2D, m_AmbientTexture);
        //            shader->setUniformValue("tAmbientColor",
        //            m_AmbientTexture);
        //
        //            glActiveTexture(GL_TEXTURE0 + 1);
        //            glBindTexture(GL_TEXTURE_2D, m_DiffuseTexture);
        //            shader->setUniformValue("tDiffuseColor",
        //            m_DiffuseTexture);
        //
        //            glActiveTexture(GL_TEXTURE0 + 2);
        //            glBindTexture(GL_TEXTURE_2D, m_NormalTexture);
        //            shader->setUniformValue("tNormal", m_NormalTexture);
        //
        //            glActiveTexture(GL_TEXTURE0 + 3);
        //            glBindTexture(GL_TEXTURE_2D, m_SpecularTexture);
        //            shader->setUniformValue("tSpecularColor",
        //            m_SpecularTexture);

        if (!shader->setUniformValue("RimLightColor", getRimLightColor()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Couldn't set RimLightColor\n");
          }
        if (!shader->setUniformValue("RimLightStart", getRimLightStart()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Couldn't set RimLightStart\n");
          }
        if (!shader->setUniformValue("RimLightEnd", getRimLightEnd()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Couldn't set RimLightEnd\n");
          }
        if (!shader->setUniformValue("RimLightCoefficient",
                                     getRimLightCoefficient()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                        "Couldn't set RimLightCoefficient\n");
          }

        if (!shader->setUniformValue("LightSourceAmbientColor",
                                     getLightSourceAmbientColor()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                        "Couldn't set LightSourceAmbientColor\n");
          }
        if (!shader->setUniformValue("LightSourceDiffuseColor",
                                     getLightSourceDiffuseColor()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                        "Couldn't set LightSourceDiffuseColor\n");
          }
        if (!shader->setUniformValue("LightSourceSpecularColor",
                                     getLightSourceSpecularColor()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                        "Couldn't set LightSourceSpecularColor\n");
          }

        if (!shader->setUniformValue("LightSourcePosition_worldspace",
                                     getLightSourcePosition()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                        "Couldn't set LightSourcePosition_worldspace\n");
          }

        if (!shader->setUniformValue("LightSourceSpotDirection",
                                     getLightSourceSpotDirection()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                        "Couldn't set LightSourceSpotDirection\n");
          }
        if (!shader->setUniformValue("LightSourceSpotExponent",
                                     getLightSourceSpotExponent()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                        "Couldn't set LightSourceSpotExponent\n");
          }

        if (!shader->setUniformValue("LightSourceSpotCutoff",
                                     getLightSourceSpotCutoff()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                        "Couldn't set LightSourceSpotCutoff\n");
          }
        if (!shader->setUniformValue("LightSourceSpotCosCutoff",
                                     getLightSourceSpotCosCutoff()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                        "Couldn't set LightSourceSpotCosCutoff\n");
          }

        if (!shader->setUniformValue("LightSourceConstantAttenuation",
                                     getLightSourceConstantAttenuation()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                        "Couldn't set LightSourceConstantAttenuation\n");
          }
        if (!shader->setUniformValue("LightSourceLinearAttenuation",
                                     getLightSourceLinearAttenuation()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                        "Couldn't set LightSourceLinearAttenuation\n");
          }
        if (!shader->setUniformValue("LightSourceQuadraticAttenuation",
                                     getLightSourceQuadraticAttenuation()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                        "Couldn't set LightSourceQuadraticAttenuation\n");
          }

        if (!shader->setUniformValue("LightAmbientColor",
                                     getLightAmbientColor()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                        "Couldn't set LightAmbientColor\n");
          }

        if (!shader->setUniformValue("MaterialShininess",
                                     getMaterialShininess()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                        "Couldn't set MaterialShininess\n");
          }

        if (!shader->setUniformValue("FogMaxDistance", getFogMaxDistance()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Couldn't set FogMaxDistance\n");
          }
        if (!shader->setUniformValue("FogMinDistance", getFogMinDistance()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Couldn't set FogMinDistance\n");
          }
        if (!shader->setUniformValue("FogColor", getFogColor()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Couldn't set FogColor\n");
          }
        if (!shader->setUniformValue("FogDensity", getFogDensity()))
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Couldn't set FogDensity\n");
          }

        m_ShaderChanged = false;

        glBindVertexArray_NJLIC(m_VertexArray);

        if (isModelViewBufferChanged())
          {
            glBindBuffer(GL_ARRAY_BUFFER, m_ModelViewBuffer);
            glBufferSubData(GL_ARRAY_BUFFER, 0,
                            getModelViewTransformArrayBufferSize(),
                            getModelViewTransformArrayBufferPtr());
            enableModelViewBufferChanged(false);
          }

        if (isNormalMatrixBufferChanged())
          {
            glBindBuffer(GL_ARRAY_BUFFER, m_NormalMatrixTransformBuffer);
            glBufferSubData(GL_ARRAY_BUFFER, 0,
                            getNormalMatrixTransformArrayBufferSize(),
                            getNormalMatrixTransformArrayBufferPtr());
            enableNormalMatrixBufferChanged(false);
          }

        if (isVertexArrayBufferChanged())
          {
            glBindBuffer(GL_ARRAY_BUFFER, m_VerticesBuffer);
            glBufferSubData(GL_ARRAY_BUFFER, 0, getVertexArrayBufferSize(),
                            getVertexArrayBufferPtr());
            enableVertexArrayBufferChanged(false);
          }

        if (isIndiceArrayBufferChanged())
          {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,
                            getElementArrayBufferSize(),
                            getElementArrayBufferPtr());
            enableIndiceArrayBufferChanged(false);
          }

        glDrawElements(GL_TRIANGLES, maxNumberOfInstances() * numberOfIndices(),
                       getElementIndexType(), (const GLvoid *)0);
        //            glDrawElements(GL_LINE_LOOP, maxNumberOfInstances() *
        //            numberOfIndices(), getElementIndexType(), (const
        //            GLvoid*)0); glDrawElements(GL_POINTS,
        //            maxNumberOfInstances() * numberOfIndices(),
        //            getElementIndexType(), (const GLvoid*)0);

        glBindVertexArray_NJLIC(0);

        if (material)
          {
            material->unBind();
          }
      }
  }

  GLsizei Geometry::maxNumberOfInstances() const { return m_NumberInstances; }

  GLsizei Geometry::maxNumberOfSubDivisions() const
  {
    return m_NumberSubDivisions;
  }

  GLsizei Geometry::subdivisionBufferSize() const
  {
    return m_ExtraSubdivisionBuffer;
  }

  unsigned long Geometry::getGeometryIndex(Node *const node) const
  {
    return node->getGeometryIndex();
  }

  void computeTangentBasis(
      // inputs
      const std::vector<btVector3> &vertices, const std::vector<btVector2> &uvs,
      const std::vector<btVector3> &normals,
      // outputs
      std::vector<btVector3> &tangents, std::vector<btVector3> &bitangents)
  {

    tangents.clear();
    bitangents.clear();
    tangents.resize(vertices.size());
    bitangents.resize(vertices.size());

    for (unsigned int i = 0; i < vertices.size(); i += 3)
      {

        // Shortcuts for vertices
        btVector3 v0 = vertices[i + 0];
        btVector3 v1 = vertices[i + 1];
        btVector3 v2 = vertices[i + 2];

        // Shortcuts for UVs
        btVector2 uv0 = uvs[i + 0];
        btVector2 uv1 = uvs[i + 1];
        btVector2 uv2 = uvs[i + 2];

        // Edges of the triangle : postion delta
        btVector3 deltaPos1 = v1 - v0;
        btVector3 deltaPos2 = v2 - v0;

        // UV delta
        btVector2 deltaUV1 = uv1 - uv0;
        btVector2 deltaUV2 = uv2 - uv0;

        float r =
            1.0f / (deltaUV1.x() * deltaUV2.y() - deltaUV1.y() * deltaUV2.x());
        btVector3 tangent =
            (deltaPos1 * deltaUV2.y() - deltaPos2 * deltaUV1.y()) * r;
        btVector3 bitangent =
            (deltaPos2 * deltaUV1.x() - deltaPos1 * deltaUV2.x()) * r;

        // Set the same tangent for all three vertices of the triangle.
        // They will be merged later, in vboindexer.cpp
        tangents[i] = tangent;
        tangents[i + 1] = tangent;
        tangents[i + 2] = tangent;

        // Same thing for binormals
        bitangents[i] = bitangent;
        bitangents[i + 1] = bitangent;
        bitangents[i + 2] = bitangent;
      }

    // See "Going Further"
    for (unsigned int i = 0; i < vertices.size(); i += 1)
      {
        btVector3 n = normals[i];
        btVector3 t = tangents[i];
        btVector3 b = bitangents[i];

        // Gram-Schmidt orthogonalize
        t = (t - n * n.dot(t)).normalized();

        // Calculate handedness
        if (n.cross(t).dot(b) < 0.0f)
          {
            t = t * -1.0f;
          }
      }
  }

  void Geometry::setRimLightColor(const btVector3 &color)
  {
    m_RimLightColor = color;
  }

  const btVector3 &Geometry::getRimLightColor() const
  {
    return m_RimLightColor;
  }

  void Geometry::setRimLightStart(const float v) { m_RimLightStart = v; }

  float Geometry::getRimLightStart() const { return m_RimLightStart; }

  void Geometry::setRimLightEnd(const float v) { m_RimLightEnd = v; }

  float Geometry::getRimLightEnd() const { return m_RimLightEnd; }

  void Geometry::setRimLightCoefficient(const float v)
  {
    m_RimLightCoefficient = v;
  }

  float Geometry::getRimLightCoefficient() const
  {
    return m_RimLightCoefficient;
  }

  void Geometry::setLightSourceAmbientColor(const btVector3 &color)
  {
    m_LightSourceAmbientColor = color;
  }

  const btVector3 &Geometry::getLightSourceAmbientColor() const
  {
    return m_LightSourceAmbientColor;
  }

  void Geometry::setLightSourceDiffuseColor(const btVector3 &color)
  {
    m_LightSourceDiffuseColor = color;
  }

  const btVector3 &Geometry::getLightSourceDiffuseColor() const
  {
    return m_LightSourceDiffuseColor;
  }

  void Geometry::setLightSourceSpecularColor(const btVector3 &color)
  {
    m_LightSourceSpecularColor = color;
  }
  const btVector3 &Geometry::getLightSourceSpecularColor() const
  {
    return m_LightSourceSpecularColor;
  }

  void Geometry::setLightSourcePosition(const btVector4 &pos)
  {
    m_LightSourcePosition_worldspace = pos;
  }

  const btVector4 &Geometry::getLightSourcePosition() const
  {
    return m_LightSourcePosition_worldspace;
  }

  void Geometry::setLightSourceSpotDirection(const btVector3 &dir)
  {
    m_LightSourceSpotDirection = dir;
  }

  const btVector3 &Geometry::getLightSourceSpotDirection() const
  {
    return m_LightSourceSpotDirection;
  }

  void Geometry::setLightSourceSpotExponent(const float v)
  {
    m_LightSourceSpotExponent = v;
  }

  float Geometry::getLightSourceSpotExponent() const
  {
    return m_LightSourceSpotExponent;
  }

  void Geometry::setLightSourceSpotCutoff(const float v)
  {
    m_LightSourceSpotCutoff = v;
  }

  float Geometry::getLightSourceSpotCutoff() const
  {
    return m_LightSourceSpotCutoff;
  }

  void Geometry::setLightSourceSpotCosCutoff(const float v)
  {
    m_LightSourceSpotCosCutoff = v;
  }
  float Geometry::getLightSourceSpotCosCutoff() const
  {
    return m_LightSourceSpotCosCutoff;
  }

  void Geometry::setLightSourceConstantAttenuation(const float v)
  {
    m_LightSourceConstantAttenuation = v;
  }

  float Geometry::getLightSourceConstantAttenuation() const
  {
    return m_LightSourceConstantAttenuation;
  }

  void Geometry::setLightSourceLinearAttenuation(const float v)
  {
    m_LightSourceLinearAttenuation = v;
  }
  float Geometry::getLightSourceLinearAttenuation() const
  {
    return m_LightSourceLinearAttenuation;
  }

  void Geometry::setLightSourceQuadraticAttenuation(const float v)
  {
    m_LightSourceQuadraticAttenuation = v;
  }
  float Geometry::getLightSourceQuadraticAttenuation() const
  {
    return m_LightSourceQuadraticAttenuation;
  }

  void Geometry::setLightAmbientColor(const btVector3 &color)
  {
    m_LightAmbientColor = color;
  }

  const btVector3 &Geometry::getLightAmbientColor() const
  {
    return m_LightAmbientColor;
  }

  void Geometry::setMaterialShininess(const float v)
  {
    m_MaterialShininess = v;
  }

  float Geometry::getMaterialShininess() const { return m_MaterialShininess; }

  void Geometry::setFogMaxDistance(const float v) { m_FogMaxDistance = v; }

  float Geometry::getFogMaxDistance() const { return m_FogMaxDistance; }

  void Geometry::setFogMinDistance(const float v) { m_FogMinDistance = v; }

  float Geometry::getFogMinDistance() const { return m_FogMinDistance; }

  void Geometry::setFogColor(const btVector3 &color) { m_FogColor = color; }

  const btVector3 &Geometry::getFogColor() const { return m_FogColor; }

  void Geometry::setFogDensity(const float v) { m_FogDensity = v; }

  float Geometry::getFogDensity() const { return m_FogDensity; }

  void Geometry::setAmbientTexture(const GLuint t) { m_AmbientTexture = t; }

  void Geometry::setDiffuseTexture(const GLuint t) { m_DiffuseTexture = t; }

  void Geometry::setNormalTexture(const GLuint t) { m_NormalTexture = t; }

  void Geometry::setSpecularTexture(const GLuint t) { m_SpecularTexture = t; }

  void Geometry::hide(Camera *camera)
  {
    //        SDL_assert(camera);
    if (camera)
      {
        m_RenderCategory = (njliBitCategories)Off(m_RenderCategory,
                                                  camera->getRenderCategory());
      }
    else
      {
        SDL_Log("Hiding geometry with a NULL camera");
      }
  }

  void Geometry::show(Camera *camera)
  {
    SDL_assert(camera);

    if (camera)
      {
        m_RenderCategory = (njliBitCategories)On(m_RenderCategory,
                                                 camera->getRenderCategory());
      }
    else
      {
        SDL_Log("Hiding geometry with a NULL camera");
      }
  }

  bool Geometry::isHidden(Camera *camera) const
  {
    return camera->hasRenderCategory(m_RenderCategory);
  }

  const void *Geometry::getModelViewTransformArrayBufferPtr() const
  {
    assert(m_ModelViewTransformData);

    return (const void *)m_ModelViewTransformData;
  }

  GLsizeiptr Geometry::getModelViewTransformArrayBufferSize() const
  {
    GLsizeiptr size =
        (sizeof(GLfloat) * 16) * maxNumberOfInstances() * numberOfVertices();
    return size;
  }

  bool Geometry::isModelViewBufferChanged() const
  {
    return m_ModelViewBufferChanged;
  }

  void Geometry::enableModelViewBufferChanged(bool changed)
  {
    m_ModelViewBufferChanged = changed;
  }

  //    const void *Geometry::getColorTransformArrayBufferPtr()const
  //    {
  //        assert(m_ColorTransformData);
  //
  //        return m_ColorTransformData;
  //    }
  //
  //    GLsizeiptr Geometry::getColorTransformArrayBufferSize()const
  //    {
  //        GLsizeiptr size = sizeof(GLfloat) * maxNumberOfInstances() *
  //        numberOfVertices() * 16; return size;
  //    }

  const void *Geometry::getNormalMatrixTransformArrayBufferPtr() const
  {
    assert(m_NormalMatrixTransformData);

    return (const void *)m_NormalMatrixTransformData;
  }

  GLsizeiptr Geometry::getNormalMatrixTransformArrayBufferSize() const
  {
    GLsizeiptr size =
        (sizeof(GLfloat) * 16) * maxNumberOfInstances() * numberOfVertices();
    return size;
  }

  bool Geometry::isNormalMatrixBufferChanged() const
  {
    return m_NormalMatrixBufferChanged;
  }

  void Geometry::enableNormalMatrixBufferChanged(bool changed)
  {
    m_NormalMatrixBufferChanged = changed;
  }

  void Geometry::loadData()
  {
    unLoadData();

    m_ModelViewTransformData =
        new GLfloat[16 * maxNumberOfInstances() * numberOfVertices() *
                    subdivisionBufferSize()];
    assert(m_ModelViewTransformData);
    memset(m_ModelViewTransformData, 0,
           getModelViewTransformArrayBufferSize() * subdivisionBufferSize());

    m_NormalMatrixTransformData =
        new GLfloat[16 * maxNumberOfInstances() * numberOfVertices() *
                    subdivisionBufferSize()];
    assert(m_NormalMatrixTransformData);
    memset(m_NormalMatrixTransformData, 0,
           getNormalMatrixTransformArrayBufferSize() * subdivisionBufferSize());

    //        unsigned long i;

    //        for (i = 0;
    //             i < (16 * maxNumberOfInstances() * numberOfVertices() *
    //             subdivisionBufferSize()); i += 16)
    //            memcpy(m_ModelViewTransformData + i,
    //            TRANSFORM_IDENTITY_MATRIX, sizeof(TRANSFORM_IDENTITY_MATRIX));
    //        for(GLsizei i = 0; i < maxNumberOfInstances(); i++)
    //            for(GLsizei j = 0; j < numberOfVertices(); j++)
    //                setVerticeTransform(i, j, btTransform::getIdentity());

    //        for (GLsizei i = 0;
    //             i < (16 * maxNumberOfInstances() * numberOfVertices() *
    //             subdivisionBufferSize()); i += 16)
    //            memcpy(m_NormalMatrixTransformData + i,
    //            TRANSFORM_IDENTITY_MATRIX, sizeof(TRANSFORM_IDENTITY_MATRIX));

    enableModelViewBufferChanged(true);
    enableNormalMatrixBufferChanged(true);
  }

  void Geometry::unLoadData()
  {
    if (m_NormalMatrixTransformData)
      delete[] m_NormalMatrixTransformData;
    m_NormalMatrixTransformData = NULL;

    if (m_ModelViewTransformData)
      delete[] m_ModelViewTransformData;
    m_ModelViewTransformData = NULL;
  }

  bool Geometry::isVertexArrayBufferChanged() const
  {
    return m_VertexBufferChanged;
  }

  void Geometry::enableVertexArrayBufferChanged(bool changed)
  {
    m_VertexBufferChanged = changed;
  }

  bool Geometry::isIndiceArrayBufferChanged() const
  {
    return m_ElementBufferChanged;
  }

  void Geometry::enableIndiceArrayBufferChanged(bool changed)
  {
    m_ElementBufferChanged = changed;
  }

  void Geometry::addReference(Node *node)
  {
    for (unsigned long i = 0; i < m_References.size(); ++i)
      {
        if (!m_References[i])
          {
            m_References[i] = true;
            node->setGeometryIndex(i);
            return;
          }
      }
  }

  void Geometry::removeReference(Node *node)
  {
    unsigned long index = getGeometryIndex(node);

    if (index < m_References.size())
      {
        m_References[index] = false;

        setHidden(node);
      }
  }

  void Geometry::setTransform(const unsigned long index,
                              const btTransform &transform)
  {
    if (index < maxNumberOfInstances())
      {
        const unsigned long STRIDE = 16 * numberOfVertices();

        transform.getOpenGLMatrix(m_MatrixBuffer);

        for (int currentVertex = 0; currentVertex < numberOfVertices();
             currentVertex++)
          {
            unsigned long p = ((index * STRIDE) + (16 * currentVertex));
            int cmp = memcmp(m_ModelViewTransformData + p, m_MatrixBuffer,
                             sizeof(GLfloat) * 16);

            if (0 != cmp)
              {
                memcpy(m_ModelViewTransformData + p, m_MatrixBuffer,
                       sizeof(GLfloat) * 16);
              }
          }
        enableModelViewBufferChanged(true);
      }
  }

  btTransform Geometry::getTransform(const unsigned long index)
  {
    btTransform transform(btTransform::getIdentity());
    if (index < maxNumberOfInstances())
      {
        const unsigned long STRIDE = 16 * numberOfVertices();

        for (int currentVertex = 0; currentVertex < numberOfVertices();
             currentVertex++)
          {
            unsigned long p = ((index * STRIDE) + (16 * currentVertex));
            memcpy(m_MatrixBuffer, m_ModelViewTransformData + p,
                   sizeof(GLfloat) * 16);
          }

        transform.setFromOpenGLMatrix(m_MatrixBuffer);
      }
    return transform;
  }

  //    void Geometry::setColorTransform(const unsigned long index, const
  //    btTransform &transform)
  //    {
  //        if (index < maxNumberOfInstances())
  //        {
  //            const unsigned long STRIDE = 16 * numberOfVertices();
  //
  //            transform.getOpenGLMatrix(m_MatrixBuffer);
  //
  //            for (int currentVertex = 0; currentVertex < numberOfVertices();
  //            currentVertex++)
  //            {
  //                unsigned long p = ((index * STRIDE) + (16 * currentVertex));
  //
  //                int cmp = memcmp(m_ColorTransformData + p,
  //                                 m_MatrixBuffer,
  //                                 sizeof(GLfloat) * 16);
  //
  //                if(0 != cmp)
  //                {
  //                    memcpy(m_ColorTransformData + p,
  //                           m_MatrixBuffer,
  //                           sizeof(GLfloat) * 16);
  //                }
  //            }
  //        }
  //    }
  //
  //    btTransform Geometry::getColorTransform(const unsigned long index)
  //    {
  //        btTransform transform(btTransform::getIdentity());
  //        if (index < maxNumberOfInstances())
  //        {
  //            const unsigned long STRIDE = 16 * numberOfVertices();
  //
  //            for (int currentVertex = 0; currentVertex < numberOfVertices();
  //            currentVertex++)
  //            {
  //                unsigned long p = ((index * STRIDE) + (16 * currentVertex));
  //                memcpy(m_MatrixBuffer,
  //                       m_ColorTransformData + p,
  //                       sizeof(GLfloat) * 16);
  //            }
  //
  //            transform.setFromOpenGLMatrix(m_MatrixBuffer);
  //        }
  //        return transform;
  //    }

  void Geometry::setNormalMatrixTransform(const unsigned long index,
                                          const btTransform &transform)
  {
    if (index < maxNumberOfInstances())
      {
        const unsigned long STRIDE = 16 * numberOfVertices();

        transform.getOpenGLMatrix(m_MatrixBuffer);

        for (int currentVertex = 0; currentVertex < numberOfVertices();
             currentVertex++)
          {
            unsigned long p = ((index * STRIDE) + (16 * currentVertex));

            int cmp = memcmp(m_NormalMatrixTransformData + p, m_MatrixBuffer,
                             sizeof(GLfloat) * 16);

            if (0 != cmp)
              {
                memcpy(m_NormalMatrixTransformData + p, m_MatrixBuffer,
                       sizeof(GLfloat) * 16);
              }
          }
        enableNormalMatrixBufferChanged(true);
      }
  }

  btTransform Geometry::getNormalMatrixTransform(const unsigned long index)
  {
    btTransform transform(btTransform::getIdentity());
    if (index < maxNumberOfInstances())
      {
        const unsigned long STRIDE = 16 * numberOfVertices();

        for (int currentVertex = 0; currentVertex < numberOfVertices();
             currentVertex++)
          {
            unsigned long p = ((index * STRIDE) + (16 * currentVertex));
            memcpy(m_MatrixBuffer, m_NormalMatrixTransformData + p,
                   sizeof(GLfloat) * 16);
          }

        transform.setFromOpenGLMatrix(m_MatrixBuffer);
      }
    return transform;
  }

  void Geometry::setMaterial(Material *material, Image *img)
  {
    SDL_assert(material != NULL);

    removeMaterial();

    m_Material = material;

    addChild(m_Material);

    if (img)
      {
        bool hasAlpha = img->getNumberOfComponents() == 4 ||
                        img->getNumberOfComponents() == 2;
        bool premultiplied = img->getNumberOfComponents() != 1 && hasAlpha;

        m_OpacityModifyRGB = false;
        if (m_blendFuncSource == GL_ONE &&
            m_blendFuncDestination == GL_ONE_MINUS_SRC_ALPHA)
          {
            if (premultiplied)
              m_OpacityModifyRGB = true;
            else
              {
                m_blendFuncSource = GL_SRC_ALPHA;
                m_blendFuncDestination = GL_ONE_MINUS_SRC_ALPHA;
              }
          }

        if (premultiplied)
          img->preMultiplyAlpha();
      }
  }

  void Geometry::removeMaterial()
  {
    if (getMaterial())
      {
        removeChild(getMaterial());
      }

    m_Material = NULL;
  }

  Material *Geometry::getMaterial()
  {
    s32 idx = getChildIndex(m_Material);
    if (idx != -1)
      return dynamic_cast<Material *>(getChild(idx));
    return NULL;
  }
  const Material *Geometry::getMaterial() const
  {
    s32 idx = getChildIndex(m_Material);
    if (idx != -1)
      return dynamic_cast<const Material *>(getChild(idx));
    return NULL;
  }
} // namespace njli

////
////  Geometry.cpp
////  JLIGameEngineTest
////
////  Created by James Folk on 11/22/14.
////  Copyright (c) 2014 James Folk. All rights reserved.
////
//
//#include "Geometry.h"
//#include "GraphicsPlatform.h"
//#include "JLIFactoryTypes.h"
//#include "LevelOfDetail.h"
//#include "Material.h"
//#include "MaterialProperty.h"
//#include "Node.h"
//#include "ShaderProgram.h"
//#include "World.h"
//#include "btTransform.h"
//
//#include "Log.h"
//#define TAG "Geometry.cpp"
//#define FORMATSTRING "{\"njli::Geometry\":[]}"
//#include "JsonJLI.h"
//#include "btPrint.h"
//
//#include "Image.h"
//
// static const u32 MAX_SPRITES = NUMBER_OF_MESHES;
//
// static const GLfloat IDENTITYMATRIX[] = {
//    1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
//};
//
// static const GLfloat COLOR_IDENTITYMATRIX[] = {
//    1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
//};
//
// namespace njli
//{
//  f32 Geometry::s_PointSize = 1;
//  f32 Geometry::s_LineWidth = 1;
//
//  Geometry::Geometry()
//      : AbstractFactoryObject(this),
//        //    m_Name("MyGeometry"),
//        m_Material(NULL), m_ShaderProgram(NULL),
//        m_projectionMatrixUniform(-1),
//        //    m_modelViewMatrixUniform(-1),
//        m_ModelviewTransform(NULL), m_ColorTransform(NULL),
//        m_modelViewBufferID(-1), m_colorTransformBufferID(-1),
//        m_InTransformAttrib(-1), m_InColorTransform(-1),
//        //    m_CurrentMeshCount(-1),
//        m_verticesBufferID(-1), indexBufferID(-1), m_vertexArrayID(-1),
//        m_InPositionAttrib(-1), m_InTexCoordAttrib(-1), m_InColorAttrib(-1),
//        m_blendFuncSource(GL_SRC_ALPHA),
//        m_blendFuncDestination(GL_ONE_MINUS_SRC_ALPHA),
//        _opacityModifyRGB(false), m_enableBlend(true),
//        m_enableDepthTest(true), m_enableStencilTest(false),
//        m_TransformDirty(true), m_ColorTransformDirty(true),
//        //    m_StartCopyTransform(std::numeric_limits<u64>::max()),
//        m_LoadGPU(false), m_setupOpacity_Material(NULL),
//        m_setupOpacity_Image(NULL), m_setupOpacity(false), m_UnLoadGPU(false),
//        //    m_setupShader(false),
//        m_bufferModified(true), m_vertexAttribChanged(false),
//        m_MatrixBuffer(new float[16]), m_maxindice(0),
//        m_RenderCategory(JLI_BIT_CATEGORY_NONE)
//  {
//    enableRenderObject();
//  }
//
//  Geometry::Geometry(const AbstractBuilder &builder)
//      : AbstractFactoryObject(this),
//        //    m_Name("MyGeometry"),
//        m_Material(NULL), m_ShaderProgram(NULL),
//        m_projectionMatrixUniform(-1),
//        //    m_modelViewMatrixUniform(-1),
//        m_ModelviewTransform(NULL), m_ColorTransform(NULL),
//        m_modelViewBufferID(-1), m_colorTransformBufferID(-1),
//        m_InTransformAttrib(-1), m_InColorTransform(-1),
//        //    m_CurrentMeshCount(-1),
//        m_verticesBufferID(-1), indexBufferID(-1), m_vertexArrayID(-1),
//        m_InPositionAttrib(-1), m_InTexCoordAttrib(-1), m_InColorAttrib(-1),
//        m_blendFuncSource(GL_SRC_ALPHA),
//        m_blendFuncDestination(GL_ONE_MINUS_SRC_ALPHA),
//        _opacityModifyRGB(false), m_enableBlend(true),
//        m_enableDepthTest(true), m_enableStencilTest(false),
//        m_TransformDirty(true), m_ColorTransformDirty(true),
//        //    m_StartCopyTransform(std::numeric_limits<u64>::max()),
//        m_LoadGPU(false), m_setupOpacity_Material(NULL),
//        m_setupOpacity_Image(NULL), m_setupOpacity(false), m_UnLoadGPU(false),
//        //    m_setupShader(false),
//        m_bufferModified(true), m_vertexAttribChanged(false),
//        m_MatrixBuffer(new float[16]), m_maxindice(0),
//        m_RenderCategory(JLI_BIT_CATEGORY_NONE)
//  {
//    enableRenderObject();
//  }
//
//  Geometry::Geometry(const Geometry &copy)
//      : AbstractFactoryObject(this),
//        //    m_Name("MyGeometry"),
//        m_Material(NULL), m_ShaderProgram(NULL),
//        m_projectionMatrixUniform(-1),
//        //    m_modelViewMatrixUniform(-1),
//        m_ModelviewTransform(NULL), m_ColorTransform(NULL),
//        m_modelViewBufferID(-1), m_colorTransformBufferID(-1),
//        m_InTransformAttrib(-1), m_InColorTransform(-1),
//        //    m_CurrentMeshCount(-1),
//        m_verticesBufferID(-1), indexBufferID(-1), m_vertexArrayID(-1),
//        m_InPositionAttrib(-1), m_InTexCoordAttrib(-1), m_InColorAttrib(-1),
//        m_InOpacityAttrib(-1), m_InHiddenAttrib(-1),
//        m_blendFuncSource(GL_SRC_ALPHA),
//        m_blendFuncDestination(GL_ONE_MINUS_SRC_ALPHA),
//        _opacityModifyRGB(false), m_enableBlend(true),
//        m_enableDepthTest(true), m_enableStencilTest(false),
//        m_TransformDirty(true), m_ColorTransformDirty(true),
//        //    m_StartCopyTransform(std::numeric_limits<u64>::max()),
//        m_LoadGPU(false), m_setupOpacity_Material(NULL),
//        m_setupOpacity_Image(NULL), m_setupOpacity(false), m_UnLoadGPU(false),
//        //    m_setupShader(false),
//        m_bufferModified(true), m_vertexAttribChanged(false),
//        m_MatrixBuffer(new float[16]), m_maxindice(0),
//        m_RenderCategory(JLI_BIT_CATEGORY_NONE)
//  {
//    enableRenderObject();
//  }
//
//  Geometry::~Geometry()
//  {
//    delete[] m_MatrixBuffer;
//    m_MatrixBuffer = NULL;
//
//    unLoadGPU_Internal();
//  }
//
//  Geometry &Geometry::operator=(const Geometry &rhs)
//  {
//    if (this != &rhs)
//      {
//      }
//    return *this;
//  }
//
//  s32 Geometry::calculateSerializeBufferSize() const
//  {
//    // TODO: calculateSerializeBufferSize
//    return 0;
//  }
//
//  void Geometry::serialize(void *dataBuffer, btSerializer *serializer) const
//  {
//    // TODO: serialize
//  }
//
//  const char *Geometry::getClassName() const { return "Geometry"; }
//
//  s32 Geometry::getType() const { return Geometry::type(); }
//
//  Geometry::operator std::string() const
//  {
//    return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
//  }
//
//  Geometry *Geometry::create(u32 type)
//  {
//    SDL_assert(type == JLI_OBJECT_TYPE_Plane);
//
//    return dynamic_cast<Geometry *>(
//        World::getInstance()->getWorldFactory()->create(type));
//  }
//
//  void Geometry::destroy(Geometry *object)
//  {
//    if (object)
//      {
//        object->removeMaterial();
//        object->removeShaderProgram();
//        object->removeAllLevelOfDetails();
//
//        World::getInstance()->getWorldFactory()->destroy(object);
//      }
//  }
//
//  void Geometry::load(Geometry &object, lua_State *L, int index)
//  {
//    // Push another reference to the table on top of the stack (so we know
//    // where it is, and this function can work for negative, positive and
//    // pseudo indices
//    lua_pushvalue(L, index);
//    // stack now contains: -1 => table
//    lua_pushnil(L);
//    // stack now contains: -1 => nil; -2 => table
//    while (lua_next(L, -2))
//      {
//        // stack now contains: -1 => value; -2 => key; -3 => table
//        // copy the key so that lua_tostring does not modify the original
//        lua_pushvalue(L, -2);
//        // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
//        const char *key = lua_tostring(L, -1);
//        //            const char *value = lua_tostring(L, -2);
//        if (lua_istable(L, -2))
//          {
//            Geometry::load(object, L, -2);
//          }
//        else
//          {
//            if (lua_isnumber(L, index))
//              {
//                double number = lua_tonumber(L, index);
//                printf("%s => %f\n", key, number);
//              }
//            else if (lua_isstring(L, index))
//              {
//                const char *v = lua_tostring(L, index);
//                printf("%s => %s\n", key, v);
//              }
//            else if (lua_isboolean(L, index))
//              {
//                bool v = lua_toboolean(L, index);
//                printf("%s => %d\n", key, v);
//              }
//            else if (lua_isuserdata(L, index))
//              {
//                //                    swig_lua_userdata *usr;
//                //                    swig_type_info *type;
//                //                    assert(lua_isuserdata(L,index));
//                // usr=(swig_lua_userdata*)lua_touserdata(L,index);
//                //                    /* get data */
//                //                    type = usr->type;
//                //                    njli::AbstractFactoryObject *object =
//                // static_cast<njli::AbstractFactoryObject*>(usr->ptr);
//                //                    printf("%s => %d:%s\n", key,
//                //                    object->getType(),
//                //                    object->getClassName());
//              }
//          }
//        // pop value + copy of key, leaving original key
//        lua_pop(L, 2);
//        // stack now contains: -1 => key; -2 => table
//      }
//    // stack now contains: -1 => table (when lua_next returns 0 it pops the
//    key
//    // but does not push anything.)
//    // Pop table
//    lua_pop(L, 1);
//    // Stack is now the same as it was on entry to this function
//  }
//
//  u32 Geometry::type() { return JLI_OBJECT_TYPE_Geometry; }
//
//  void Geometry::addLevelOfDetail(LevelOfDetail *lod)
//  {
//    SDL_assert(NULL != lod);
//
//    std::vector<LevelOfDetail *>::const_iterator iter =
//        std::find(m_LevelOfDetailList.begin(), m_LevelOfDetailList.end(),
//        lod);
//
//    if (iter == m_LevelOfDetailList.end())
//      {
//        std::vector<LevelOfDetail *>::iterator iter = std::find(
//            m_LevelOfDetailList.begin(), m_LevelOfDetailList.end(), lod);
//
//        if (iter != m_LevelOfDetailList.end())
//          removeLevelOfDetail(lod);
//
//        m_LevelOfDetailList.push_back(lod);
//
//        addChild(lod);
//      }
//  }
//
//  bool Geometry::removeLevelOfDetail(LevelOfDetail *lod)
//  {
//    SDL_assert(NULL != lod);
//
//    std::vector<LevelOfDetail *>::iterator iter =
//        std::find(m_LevelOfDetailList.begin(), m_LevelOfDetailList.end(),
//        lod);
//
//    if (iter != m_LevelOfDetailList.end())
//      {
//        removeChild(*iter);
//        m_LevelOfDetailList.erase(iter);
//        return true;
//      }
//    return false;
//  }
//
//  void Geometry::removeAllLevelOfDetails()
//  {
//    for (std::vector<LevelOfDetail *>::iterator iter =
//             m_LevelOfDetailList.begin();
//         iter != m_LevelOfDetailList.end(); ++iter)
//      {
//        removeChild(*iter);
//      }
//    m_LevelOfDetailList.clear();
//  }
//
//  void Geometry::getLevelOfDetails(
//      std::vector<LevelOfDetail *> &particleEmitters) const
//  {
//    for (std::vector<LevelOfDetail *>::const_iterator iter =
//             m_LevelOfDetailList.begin();
//         iter != m_LevelOfDetailList.end(); ++iter)
//      {
//        if (getChildIndex(*iter) != -1)
//          particleEmitters.push_back(*iter);
//      }
//  }
//
//  LevelOfDetail *Geometry::getLevelOfDetail(const u32 index)
//  {
//    if (index < m_LevelOfDetailList.size())
//      {
//        s32 idx = getChildIndex(m_LevelOfDetailList.at(index));
//        if (idx != -1)
//          return dynamic_cast<LevelOfDetail *>(getChild(idx));
//      }
//    return NULL;
//  }
//
//  const LevelOfDetail *Geometry::getLevelOfDetail(const u32 index) const
//  {
//    if (index < m_LevelOfDetailList.size())
//      {
//        s32 idx = getChildIndex(m_LevelOfDetailList.at(index));
//        if (idx != -1)
//          return dynamic_cast<const LevelOfDetail *>(getChild(idx));
//      }
//    return NULL;
//  }
//
//  void Geometry::setMaterial(Material *material, Image *img)
//  {
//    SDL_assert(material != NULL);
//
//    removeMaterial();
//
//    m_Material = material;
//
//    addChild(m_Material);
//
//    if (img)
//      {
//        bool hasAlpha = img->getNumberOfComponents() == 4 ||
//                        img->getNumberOfComponents() == 2;
//        bool premultiplied = img->getNumberOfComponents() != 1 && hasAlpha;
//
//        _opacityModifyRGB = false;
//        if (m_blendFuncSource == GL_ONE &&
//            m_blendFuncDestination == GL_ONE_MINUS_SRC_ALPHA)
//          {
//            if (premultiplied)
//              _opacityModifyRGB = true;
//            else
//              {
//                m_blendFuncSource = GL_SRC_ALPHA;
//                m_blendFuncDestination = GL_ONE_MINUS_SRC_ALPHA;
//              }
//          }
//
//        if (premultiplied)
//          img->preMultiplyAlpha();
//      }
//  }
//
//  void Geometry::removeMaterial()
//  {
//    if (getMaterial())
//      {
//        removeChild(getMaterial());
//      }
//
//    m_Material = NULL;
//  }
//
//  Material *Geometry::getMaterial()
//  {
//    s32 idx = getChildIndex(m_Material);
//    if (idx != -1)
//      return dynamic_cast<Material *>(getChild(idx));
//    return NULL;
//  }
//  const Material *Geometry::getMaterial() const
//  {
//    s32 idx = getChildIndex(m_Material);
//    if (idx != -1)
//      return dynamic_cast<const Material *>(getChild(idx));
//    return NULL;
//  }
//
//  void Geometry::setShaderProgram(ShaderProgram *shader)
//  {
//    SDL_assert(shader != NULL);
//
//    removeShaderProgram();
//
//    m_ShaderProgram = shader;
//
//    addChild(m_ShaderProgram);
//
//    setupShader();
//  }
//
//  void Geometry::removeShaderProgram()
//  {
//    ShaderProgram *shader = getShaderProgram();
//    if (NULL != shader)
//      {
//        removeChild(shader);
//      }
//
//    m_ShaderProgram = NULL;
//  }
//
//  ShaderProgram *Geometry::getShaderProgram()
//  {
//    s32 idx = getChildIndex(m_ShaderProgram);
//    if (idx != -1)
//      return dynamic_cast<ShaderProgram *>(getChild(idx));
//    return NULL;
//  }
//
//  const ShaderProgram *Geometry::getShaderProgram() const
//  {
//    s32 idx = getChildIndex(m_ShaderProgram);
//    if (idx != -1)
//      return dynamic_cast<const ShaderProgram *>(getChild(idx));
//    return NULL;
//  }
//
//  u32 Geometry::getMaxMeshes() const { return MAX_SPRITES; }
//
//  //  void Geometry::setHidden(Node *node, Camera *camera)
//  //  {
//  //    if (node->isHidden(camera))
//  //      {
//  //        this->hide(camera);
//  //      }
//  //    else if (!node->isHidden(camera))
//  //      {
//  //        this->show(camera);
//  //      }
//  //    this->setHidden(node, node->isHidden(camera));
//  //  }
//
//  void Geometry::setBlendSource(s32 source) { m_blendFuncSource = source; }
//
//  void Geometry::setBlendDestination(s32 dest)
//  {
//    m_blendFuncDestination = dest;
//  }
//
//  void Geometry::setupOpacity(Material *material, Image *img)
//  {
//    m_setupOpacity_Material = material;
//    m_setupOpacity_Image = img;
//    m_setupOpacity = true;
//  }
//
//  void Geometry::loadGPU() { m_LoadGPU = true; }
//
//  void Geometry::unLoadGPU() { m_UnLoadGPU = true; }
//
//  bool Geometry::isLoadedGPU() const { return (m_verticesBufferID != -1); }
//
//  void Geometry::sort(const btVector3 &cameraOrigin)
//  {
//    quickSort(0, m_maxindice, cameraOrigin);
//    m_maxindice = 0;
//  }
//
//  void Geometry::quickSort(signed long left, signed long right,
//                           const btVector3 &cameraOrigin)
//  {
//    SDL_assert(left >= 0 && left < getMaxMeshes());
//    SDL_assert(right >= 0 && right < getMaxMeshes());
//
//    signed long i = left, j = right;
//    signed long pivot = (left + right) / 2;
//
//    while (i <= j)
//      {
//        while (lessThan(i, pivot, cameraOrigin))
//          ++i;
//        while (greaterThan(j, pivot, cameraOrigin))
//          --j;
//        if (i <= j)
//          {
//            swapTransformData(i, j);
//            //                swapVertexData(i, j);
//
//            ++i;
//            --j;
//          }
//      }
//
//    if (left < j)
//      quickSort(left, j, cameraOrigin);
//    if (i < right)
//      quickSort(i, right, cameraOrigin);
//  }
//
//  void Geometry::swapTransformData(const size_t idx1, const size_t idx2)
//  {
//    btTransform temp(getTransform(idx1));
//    setTransform(idx1, getTransform(idx2));
//    setTransform(idx2, temp);
//  }
//  bool Geometry::lessThan(const size_t idx1, const size_t idx2,
//                          const btVector3 &cameraOrigin)
//  {
//    btVector3 object1(getTransform(idx1).getOrigin());
//    btVector3 object2(getTransform(idx2).getOrigin());
//
//    return cameraOrigin.distance2(object1) < cameraOrigin.distance2(object2);
//  }
//
//  bool Geometry::greaterThan(const size_t idx1, const size_t idx2,
//                             const btVector3 &cameraOrigin)
//  {
//    btVector3 object1(getTransform(idx1).getOrigin());
//    btVector3 object2(getTransform(idx2).getOrigin());
//
//    return cameraOrigin.distance2(object1) > cameraOrigin.distance2(object2);
//  }
//
//  void Geometry::setTransform(const u64 index, const btTransform &transform)
//  {
//    if (index < getMaxMeshes())
//      {
//        const GLuint STRIDE = 64;
//
//        transform.getOpenGLMatrix(m_MatrixBuffer);
//
//        m_TransformDirty = true;
//        for (int currentVertex = 0; currentVertex < numberOfVertices();
//             currentVertex++)
//          {
//            u64 p = ((index * STRIDE) + (16 * currentVertex));
//            int cmp = memcmp(m_ModelviewTransform + p, m_MatrixBuffer,
//                             sizeof(f32) * 16);
//
//            if (0 != cmp)
//              {
//                memcpy(m_ModelviewTransform + p, m_MatrixBuffer,
//                       sizeof(f32) * 16);
//                m_TransformDirty = true;
//              }
//          }
//        m_maxindice = std::max<u64>(index, m_maxindice);
//      }
//  }
//
//  btTransform Geometry::getTransform(const u64 index)
//  {
//    btTransform transform(btTransform::getIdentity());
//    if (index < getMaxMeshes())
//      {
//        const GLuint STRIDE = 64;
//
//        for (int currentVertex = 0; currentVertex < numberOfVertices();
//             currentVertex++)
//          {
//            u64 p = ((index * STRIDE) + (16 * currentVertex));
//            memcpy(m_MatrixBuffer, m_ModelviewTransform + p, sizeof(f32) *
//            16);
//          }
//
//        transform.setFromOpenGLMatrix(m_MatrixBuffer);
//      }
//    return transform;
//  }
//
//  void Geometry::setColorTransform(const u64 index,
//                                   const btTransform &transform)
//  {
//    if (index < getMaxMeshes())
//      {
//        const GLuint STRIDE = 64;
//
//        transform.getOpenGLMatrix(m_MatrixBuffer);
//
//        m_ColorTransformDirty = false;
//        for (int currentVertex = 0; currentVertex < numberOfVertices();
//             currentVertex++)
//          {
//            u64 p = ((index * STRIDE) + (16 * currentVertex));
//
//            int cmp =
//                memcmp(m_ColorTransform + p, m_MatrixBuffer, sizeof(f32) *
//                16);
//
//            if (0 != cmp)
//              {
//                memcpy(m_ColorTransform + p, m_MatrixBuffer, sizeof(f32) *
//                16); m_ColorTransformDirty = true;
//              }
//          }
//      }
//  }
//
//  btTransform Geometry::getColorTransform(const u64 index)
//  {
//    btTransform transform(btTransform::getIdentity());
//    if (index < getMaxMeshes())
//      {
//        const GLuint STRIDE = 64;
//
//        for (int currentVertex = 0; currentVertex < numberOfVertices();
//             currentVertex++)
//          {
//            u64 p = ((index * STRIDE) + (16 * currentVertex));
//            memcpy(m_MatrixBuffer, m_ColorTransform + p, sizeof(f32) * 16);
//          }
//
//        transform.setFromOpenGLMatrix(m_MatrixBuffer);
//      }
//    return transform;
//  }
//
//  void Geometry::getAabb(Node *node, btVector3 &aabbMin,
//                         btVector3 &aabbMax) const
//  {
//    aabbMin = btVector3(0, 0, 0);
//    aabbMax = btVector3(0, 0, 0);
//  }
//
//  void Geometry::enableBlend(const bool enable) { m_enableBlend = enable; }
//
//  void Geometry::enableDepthTest(const bool enable)
//  {
//    m_enableDepthTest = enable;
//  }
//
//  void Geometry::enableStencilTest(const bool enable)
//  {
//    m_enableStencilTest = enable;
//  }
//
//  void Geometry::hide(Camera *camera)
//  {
//    //        SDL_assert(camera);
//    if (camera)
//      {
//        m_RenderCategory = (njliBitCategories)Off(m_RenderCategory,
//                                                  camera->getRenderCategory());
//      }
//    else
//      {
//        SDL_Log("Hiding geometry with a NULL camera");
//      }
//  }
//
//  void Geometry::show(Camera *camera)
//  {
//    SDL_assert(camera);
//
//    m_RenderCategory =
//        (njliBitCategories)On(m_RenderCategory, camera->getRenderCategory());
//  }
//
//  bool Geometry::isHidden(Camera *camera) const
//  {
//    return !camera->hasRenderCategory(m_RenderCategory);
//  }
//
//  void Geometry::load()
//  {
//    unLoad();
//
//    m_ModelviewTransform = new f32[MAX_SPRITES * numberOfVertices() * 16];
//    memset(m_ModelviewTransform, 0,
//           sizeof(f32) * MAX_SPRITES * numberOfVertices() * 16);
//
//    m_TransformDirty = true;
//    //        m_StartCopyTransform = 0;
//
//    for (int i = 0; i < MAX_SPRITES * numberOfVertices() * 16; i += 16)
//      {
//        memcpy(m_ModelviewTransform + i, IDENTITYMATRIX,
//               sizeof(IDENTITYMATRIX));
//      }
//
//    m_ColorTransform = new f32[MAX_SPRITES * numberOfVertices() * 16];
//    memset(m_ColorTransform, 0,
//           sizeof(f32) * MAX_SPRITES * numberOfVertices() * 16);
//
//    m_ColorTransformDirty = true;
//    //        m_StartCopyTransform = 0;
//
//    for (int i = 0; i < MAX_SPRITES * numberOfVertices() * 16; i += 16)
//      {
//        memcpy(m_ColorTransform + i, COLOR_IDENTITYMATRIX,
//               sizeof(COLOR_IDENTITYMATRIX));
//      }
//
//    m_References.reset();
//    //        std::string ids = m_References.to_string();
//    //        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "reset\t%s", ids.c_str());
//  }
//  void Geometry::unLoad()
//  {
//    if (m_ModelviewTransform)
//      delete[] m_ModelviewTransform;
//    m_ModelviewTransform = NULL;
//
//    if (m_ColorTransform)
//      delete[] m_ColorTransform;
//    m_ColorTransform = NULL;
//  }
//
//  void Geometry::render(Camera *camera, s32 mode)
//  {
//#if !(defined(NDEBUG)) && defined(__APPLE__)
//    GLchar buffer[2048];
//    sprintf(buffer, "%s, %s", getName(), camera->getName());
//    glPushGroupMarkerEXT(0, buffer);
//#endif
//    Material *material = getMaterial();
//    ShaderProgram *shader = getShaderProgram();
//
//    if (m_UnLoadGPU)
//      unLoadGPU_Internal();
//
//    if (m_setupOpacity)
//      setupOpacity_Internal(m_setupOpacity_Material, m_setupOpacity_Image);
//
//    glLineWidth(s_LineWidth);
//
//    if (m_LoadGPU)
//      loadGPU_Internal();
//
//    //        if(m_setupShader)
//    //            setupShader_Internal();
//
//    if (m_enableBlend)
//      {
//        glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//        glBlendEquation(GL_FUNC_ADD);
//      }
//    else
//      {
//        glDisable(GL_BLEND);
//      }
//
//    if (m_enableDepthTest)
//      glEnable(GL_DEPTH_TEST);
//    else
//      glDisable(GL_DEPTH_TEST);
//
//    if (m_enableStencilTest)
//      glEnable(GL_STENCIL_TEST);
//    else
//      glDisable(GL_STENCIL_TEST);
//
//    if (!isLoadedGPU())
//      {
//        m_LoadGPU = true;
//        loadGPU_Internal();
//      }
//
//#if defined(__APPLE__)
//    glBindVertexArrayAPPLE(m_vertexArrayID);
//#else
//    glBindVertexArray(m_vertexArrayID);
//#endif
//
//    if (NULL != shader)
//      {
//        if (shader->use())
//          {
//            if (NULL != material)
//              material->bind(shader);
//
//            shader->setUniformValue("modelView", camera->getModelView());
//            //        shader->setUniformValue("projection",
//            //        camera->getProjection());
//
//            //        glUniformMatrix4fv(m_modelViewMatrixUniform, 1, 0,
//            //        camera->getModelViewMatrixArray());
//            glUniformMatrix4fv(m_projectionMatrixUniform, 1, 0,
//                               camera->getProjectionMatrixArray());
//            //        glUniform1i(u_opacityModifyRGB, _opacityModifyRGB);
//            shader->setUniformValue("u_opacityModifyRGB", _opacityModifyRGB);
//          }
//      }
//
//    bindTransform();
//    bindColorTransform();
//
//    if (isBufferModified())
//      {
//        glBindBuffer(GL_ARRAY_BUFFER, m_verticesBufferID);
//        glBufferSubData(GL_ARRAY_BUFFER, 0, (GLsizeiptr)getArrayBufferSize(),
//                        getArrayBuffer());
//        m_bufferModified = false;
//        //            printf("buffer");
//
//        if (m_vertexAttribChanged)
//          {
//            //
//
//            glEnableVertexAttribArray(m_InPositionAttrib);
//            glVertexAttribPointer(
//                m_InPositionAttrib, 3, GL_FLOAT, GL_FALSE,
//                sizeof(TexturedColoredVertex),
//                (const GLvoid *)offsetof(TexturedColoredVertex, vertex));
//
//            glEnableVertexAttribArray(m_InTexCoordAttrib);
//            glVertexAttribPointer(
//                m_InTexCoordAttrib, 2, GL_FLOAT, GL_FALSE,
//                sizeof(TexturedColoredVertex),
//                (const GLvoid *)offsetof(TexturedColoredVertex, texture));
//
//            glEnableVertexAttribArray(m_InColorAttrib);
//            glVertexAttribPointer(
//                m_InColorAttrib, 4, GL_FLOAT, GL_FALSE,
//                sizeof(TexturedColoredVertex),
//                (const GLvoid *)offsetof(TexturedColoredVertex, color));
//
//            glEnableVertexAttribArray(m_InOpacityAttrib);
//            glVertexAttribPointer(
//                m_InOpacityAttrib, 1, GL_FLOAT, GL_FALSE,
//                sizeof(TexturedColoredVertex),
//                (const GLvoid *)offsetof(TexturedColoredVertex, opacity));
//
//            glEnableVertexAttribArray(m_InHiddenAttrib);
//            glVertexAttribPointer(
//                m_InHiddenAttrib, 1, GL_FLOAT, GL_FALSE,
//                sizeof(TexturedColoredVertex),
//                (const GLvoid *)offsetof(TexturedColoredVertex, hidden));
//          }
//
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
//
//        glDrawElements(
//            mode, static_cast<GLsizei>((getMaxMeshes()) * numberOfIndices()),
//            GL_UNSIGNED_SHORT, (const GLvoid *)0);
//
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//      }
//    m_vertexAttribChanged = false;
//
//    if (material)
//      material->unBind();
//
//    glDisable(GL_STENCIL_TEST);
//    glDisable(GL_DEPTH_TEST);
//    glDisable(GL_BLEND);
//
//#if !(defined(NDEBUG)) && defined(__APPLE__)
//    glPopGroupMarkerEXT();
//#endif
//  }
//
//  //    void Geometry::setupShader()
//  //    {
//  //        m_setupShader = true;
//  //
//  //    }
//
//  void Geometry::bindTransform()
//  {
//    if (m_TransformDirty)
//      {
//        const GLuint STRIDE = 64;
//
//        glBindBuffer(GL_ARRAY_BUFFER, m_modelViewBufferID);
//
//        GLsizei size =
//            sizeof(GLfloat) * getMaxMeshes() * numberOfVertices() * 16;
//
//        glBufferSubData(GL_ARRAY_BUFFER, 0, size, m_ModelviewTransform);
//
//        if (m_vertexAttribChanged)
//          {
//            glEnableVertexAttribArray(m_InTransformAttrib + 0);
//            glEnableVertexAttribArray(m_InTransformAttrib + 1);
//            glEnableVertexAttribArray(m_InTransformAttrib + 2);
//            glEnableVertexAttribArray(m_InTransformAttrib + 3);
//            glVertexAttribPointer(m_InTransformAttrib + 0, 4, GL_FLOAT, 0,
//                                  STRIDE, (GLvoid *)0);
//            glVertexAttribPointer(m_InTransformAttrib + 1, 4, GL_FLOAT, 0,
//                                  STRIDE, (GLvoid *)16);
//            glVertexAttribPointer(m_InTransformAttrib + 2, 4, GL_FLOAT, 0,
//                                  STRIDE, (GLvoid *)32);
//            glVertexAttribPointer(m_InTransformAttrib + 3, 4, GL_FLOAT, 0,
//                                  STRIDE, (GLvoid *)48);
//          }
//
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//        m_TransformDirty = false;
//      }
//  }
//
//  void Geometry::bindColorTransform()
//  {
//    if (m_ColorTransformDirty)
//      {
//        const GLuint STRIDE = 64;
//
//        glBindBuffer(GL_ARRAY_BUFFER, m_colorTransformBufferID);
//
//        GLsizei size =
//            sizeof(GLfloat) * getMaxMeshes() * numberOfVertices() * 16;
//
//        glBufferSubData(GL_ARRAY_BUFFER, 0, size, m_ColorTransform);
//
//        if (m_vertexAttribChanged)
//          {
//            glEnableVertexAttribArray(m_InColorTransform + 0);
//            glEnableVertexAttribArray(m_InColorTransform + 1);
//            glEnableVertexAttribArray(m_InColorTransform + 2);
//            glEnableVertexAttribArray(m_InColorTransform + 3);
//            glVertexAttribPointer(m_InColorTransform + 0, 4, GL_FLOAT, 0,
//                                  STRIDE, (GLvoid *)0);
//            glVertexAttribPointer(m_InColorTransform + 1, 4, GL_FLOAT, 0,
//                                  STRIDE, (GLvoid *)16);
//            glVertexAttribPointer(m_InColorTransform + 2, 4, GL_FLOAT, 0,
//                                  STRIDE, (GLvoid *)32);
//            glVertexAttribPointer(m_InColorTransform + 3, 4, GL_FLOAT, 0,
//                                  STRIDE, (GLvoid *)48);
//          }
//
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//        m_ColorTransformDirty = false;
//      }
//  }
//
//  //    void Geometry::resetMeshCount()
//  //    {
//  //        m_CurrentMeshCount = -1;
//  //    }
//
//  Node *Geometry::getParent()
//  {
//    return dynamic_cast<Node *>(AbstractDecorator::getParent());
//  }
//
//  const Node *Geometry::getParent() const
//  {
//    return dynamic_cast<const Node *>(AbstractDecorator::getParent());
//  }
//
//  void Geometry::addReference(Node *node)
//  {
//    for (s32 i = 0; i < m_References.size(); ++i)
//      {
//        if (!m_References[i])
//          {
//            m_References[i] = 1;
//
//            //                std::string ids = m_References.to_string();
//            //                SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "add\t%s",
//            //                ids.c_str());
//
//            node->setGeometryIndex(i);
//            return;
//          }
//      }
//  }
//  void Geometry::removeReference(Node *node)
//  {
//    size_t index = node->getGeometryIndex();
//    if (index < m_References.size())
//      {
//        m_References[index] = 0;
//
//        //            std::string ids = m_References.to_string();
//        //            SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "remove\t%s",
//        //            ids.c_str());
//
//        hideGeometry(node);
//      }
//  }
//
//  void Geometry::enableBufferModified(bool modified)
//  {
//    m_bufferModified = modified;
//  }
//
//  bool Geometry::isBufferModified() const { return m_bufferModified; }
//
//  void Geometry::setPointSize(const f32 s) { s_PointSize = s; }
//
//  f32 Geometry::getPointSize() { return s_PointSize; }
//
//  void Geometry::setLineWidth(const f32 s)
//  {
//    SDL_assert(s >= 0.0);
//    s_LineWidth = s;
//  }
//
//  f32 Geometry::getLineWidth() { return s_LineWidth; }
//
//  s32 Geometry::numberOfReferences() const { return m_References.size(); }
//
//  void Geometry::loadGPU_Internal()
//  {
//    SDL_assert(m_LoadGPU);
//
//    SDL_assert(m_vertexArrayID == -1);
//#if defined(__APPLE__)
//    glGenVertexArraysAPPLE(1, &m_vertexArrayID);
//    glBindVertexArrayAPPLE(m_vertexArrayID);
//#else
//    glGenVertexArrays(1, &m_vertexArrayID);
//    glBindVertexArray(m_vertexArrayID);
//#endif
//    {
//      {
//        SDL_assert(m_modelViewBufferID == -1);
//        glGenBuffers(1, &m_modelViewBufferID);
//        glBindBuffer(GL_ARRAY_BUFFER, m_modelViewBufferID);
//
//        GLsizei size =
//            sizeof(GLfloat) * getMaxMeshes() * numberOfVertices() * 16;
//        glBufferData(GL_ARRAY_BUFFER, size, m_ModelviewTransform,
//                     GL_DYNAMIC_DRAW);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//      }
//
//      {
//        SDL_assert(m_colorTransformBufferID == -1);
//        glGenBuffers(1, &m_colorTransformBufferID);
//        glBindBuffer(GL_ARRAY_BUFFER, m_colorTransformBufferID);
//
//        GLsizei size =
//            sizeof(GLfloat) * getMaxMeshes() * numberOfVertices() * 16;
//        glBufferData(GL_ARRAY_BUFFER, size, m_ColorTransform,
//        GL_DYNAMIC_DRAW); glBindBuffer(GL_ARRAY_BUFFER, 0);
//      }
//
//      {
//        SDL_assert(m_verticesBufferID == -1);
//        glGenBuffers(1, &m_verticesBufferID);
//        glBindBuffer(GL_ARRAY_BUFFER, m_verticesBufferID);
//        glBufferData(GL_ARRAY_BUFFER, (long)getArrayBufferSize(),
//                     getArrayBuffer(), GL_DYNAMIC_DRAW);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//      }
//
//      {
//        SDL_assert(indexBufferID == -1);
//        glGenBuffers(1, &indexBufferID);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
//        (long)getElementArrayBufferSize(),
//                     getElementArrayBuffer(), GL_STATIC_DRAW);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//      }
//    }
//#if defined(__APPLE__)
//    glBindVertexArrayAPPLE(0);
//#else
//    glBindVertexArray(0);
//#endif
//
//    m_LoadGPU = false;
//  }
//
//  void Geometry::setupOpacity_Internal(Material *material, Image *img)
//  {
//    SDL_assert(m_setupOpacity);
//
//    bool hasAlpha =
//        img->getNumberOfComponents() == 4 || img->getNumberOfComponents() ==
//        2;
//    bool premultiplied = img->getNumberOfComponents() != 1 && hasAlpha;
//
//    _opacityModifyRGB = false;
//    if (m_blendFuncSource == GL_ONE &&
//        m_blendFuncDestination == GL_ONE_MINUS_SRC_ALPHA)
//      {
//        if (premultiplied)
//          _opacityModifyRGB = true;
//        else
//          {
//            m_blendFuncSource = GL_SRC_ALPHA;
//            m_blendFuncDestination = GL_ONE_MINUS_SRC_ALPHA;
//          }
//      }
//
//    if (premultiplied)
//      img->preMultiplyAlpha();
//
//    material->getDiffuse()->loadGPU(*img);
//
//    m_setupOpacity = false;
//  }
//
//  void Geometry::unLoadGPU_Internal()
//  {
//    unLoadGPU();
//
//    SDL_assert(m_UnLoadGPU);
//
//    if (m_modelViewBufferID == -1)
//      {
//        glDeleteBuffers(1, &m_modelViewBufferID);
//        m_modelViewBufferID = -1;
//      }
//
//    if (m_colorTransformBufferID == -1)
//      {
//        glDeleteBuffers(1, &m_colorTransformBufferID);
//        m_colorTransformBufferID = -1;
//      }
//
//    if (indexBufferID == -1)
//      {
//        glDeleteBuffers(1, &indexBufferID);
//        indexBufferID = -1;
//      }
//
//    if (m_verticesBufferID == -1)
//      {
//        glDeleteBuffers(1, &m_verticesBufferID);
//        m_verticesBufferID = -1;
//      }
//
//    if (m_vertexArrayID == -1)
//      {
//#if defined(__APPLE__)
//        glDeleteVertexArraysAPPLE(1, &m_vertexArrayID);
//#else
//        glDeleteVertexArrays(1, &m_vertexArrayID);
//#endif
//        m_vertexArrayID = -1;
//      }
//
//    m_UnLoadGPU = false;
//  }
//
//  void Geometry::setupShader()
//  {
//    //        SDL_assert(m_setupShader);
//
//    ShaderProgram *shader = getShaderProgram();
//
//    SDL_assert(shader);
//
//    if (!shader->isLinked())
//      {
//        if (!shader->link())
//          {
//            //                SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s\n",
//            //                shader->programLog());
//            //                SDL_LogError(SDL_LOG_CATEGORY_TEST, "Vertex log:
//            //                %s\n", shader->vertexShaderLog());
//            //                SDL_LogError(SDL_LOG_CATEGORY_TEST, "Fragment
//            log:
//            //                %s\n", shader->fragmentShaderLog());
//          }
//      }
//    if (shader->isLinked())
//      {
//        shader->use();
//        // ... and add the attributes the shader needs for the vertex
//        position,
//        // color and texture st information
//        shader->bindAttribute("inPosition");
//        shader->bindAttribute("inTexCoord");
//        shader->bindAttribute("inColor");
//        shader->bindAttribute("inOpacity");
//        shader->bindAttribute("inHidden");
//
//        shader->bindAttribute("inTransform");
//        shader->bindAttribute("inColorTransform");
//
//        // Setup the index pointers into the shader for our attributes
//        m_InPositionAttrib = shader->getAttributeLocation("inPosition");
//        m_InTexCoordAttrib = shader->getAttributeLocation("inTexCoord");
//        m_InColorAttrib = shader->getAttributeLocation("inColor");
//        m_InOpacityAttrib = shader->getAttributeLocation("inOpacity");
//        m_InHiddenAttrib = shader->getAttributeLocation("inHidden");
//
//        m_InTransformAttrib = shader->getAttributeLocation("inTransform");
//        m_InColorTransform = shader->getAttributeLocation("inColorTransform");
//
//        //        m_modelViewMatrixUniform =
//        //        shader->getUniformLocation("modelView");
//        m_projectionMatrixUniform = shader->getUniformLocation("projection");
//        //        u_opacityModifyRGB =
//        //        shader->getUniformLocation("u_opacityModifyRGB");
//        //        u_pointSize = shader->getUniformLocation("u_pointSize");
//
//        //        m_setupShader = false;
//        m_vertexAttribChanged = true;
//      }
//  }
//} // namespace njli
