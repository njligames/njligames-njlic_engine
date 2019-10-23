//
//  Geometry.h
//  TeapotExplosion
//
//  Created by James Folk on 12/8/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#ifndef Geometry_h
#define Geometry_h

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "GraphicsPlatform.h"

//#include <bitset>
#include <vector>
#include <string>

#include "btTransform.h"
#include "btVector2.h"

#include "lua.hpp"
#include "JLIFactoryTypes.h"

namespace njli
{
    static const GLfloat TRANSFORM_IDENTITY_MATRIX[] =
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    };
    
    ATTRIBUTE_ALIGNED16(struct)
    TexturedColoredVertex
    {
        static void computeTangentBasis(TexturedColoredVertex *v, unsigned int numVerts)
        {
            for (unsigned int i=0; i<numVerts; i+=3 )
            {
                // Shortcuts for vertices
                btVector3  v0 = (v + (i + 0))->vertex;
                btVector3  v1 = (v + (i + 1))->vertex;
                btVector3  v2 = (v + (i + 2))->vertex;
                
                // Shortcuts for UVs
                btVector2  uv0 = (v + (i + 0))->texture;
                btVector2  uv1 = (v + (i + 1))->texture;
                btVector2  uv2 = (v + (i + 2))->texture;
                
                // Edges of the triangle : postion delta
                btVector3 deltaPos1 = v1-v0;
                btVector3 deltaPos2 = v2-v0;
                
                // UV delta
                btVector2 deltaUV1 = uv1-uv0;
                btVector2 deltaUV2 = uv2-uv0;
                
                float d = (deltaUV1.x() * deltaUV2.y() - deltaUV1.y() * deltaUV2.x());
                
                float r = (d!=0.0f)?(1.0f / d):0.0f;
                btVector3 tangent = (deltaPos1 * deltaUV2.y()   - deltaPos2 * deltaUV1.y())*r;
                btVector3 bitangent = (deltaPos2 * deltaUV1.x()   - deltaPos1 * deltaUV2.x())*r;
                
                // Set the same tangent for all three vertices of the triangle.
                // They will be merged later, in vboindexer.cpp
                (v + (i + 0))->tangent = tangent;
                (v + (i + 1))->tangent = tangent;
                (v + (i + 2))->tangent = tangent;
                
                // Same thing for binormals
                (v + (i + 0))->bitangent = bitangent;
                (v + (i + 1))->bitangent = bitangent;
                (v + (i + 2))->bitangent = bitangent;
            }
            
            // See "Going Further"
            //            for (unsigned int i=0; i<numVerts; i+=1 )
            //            {
            //                btVector3 & n = (v + (i))->normal;
            //                btVector3 & t = (v + (i))->tangent;
            //                btVector3 & b = (v + (i))->bitangent;
            //
            //
            //                // Gram-Schmidt orthogonalize
            //                t = (t - n * n.dot(t));
            //
            //                if(t.length() > 0.0f)
            //                    t.normalize();
            //
            //                // Calculate handedness
            //                if (n.cross(t).dot(b) < 0.0f)
            //                {
            //                    t = t * -1.0f;
            //                }
            //            }
        }
        
        TexturedColoredVertex()
        : vertex(0, 0, 0)
        , color(1, 1, 1, 0)
        , texture(0, 0)
        , normal(0,0,0)
        , tangent(0, 0, 0)
        , bitangent(0, 0, 0)
        {
        }
        TexturedColoredVertex(const btVector3 &vertex,
                              const btVector4 &color,
                              const btVector2 &texture,
                              const btVector3 &normal,
                              const btVector3 &tangent,
                              const btVector3 &bitangent
                              )
        : vertex(vertex)
        , color(color)
        , texture(texture)
        , normal(normal)
        , tangent(tangent)
        , bitangent(bitangent)
        {
        }
        btVector3 vertex;
        btVector4 color;
        btVector2 texture;
        btVector3 normal;
        btVector3 tangent;
        btVector3 bitangent;
        
        TexturedColoredVertex& operator=(const TexturedColoredVertex& rhs)
        {
            if (this != &rhs) {
                vertex = rhs.vertex;
                color = rhs.color;
                texture = rhs.texture;
                normal = rhs.normal;
                tangent = rhs.tangent;
                bitangent = rhs.bitangent;
            }
            return *this;
        }
        
        operator std::string() const
        {
            char buffer[4098];
            sprintf(buffer, "{{%f, %f, %f}, {%f, %f}, {%f, %f, %f}}",
                    vertex.x(), vertex.y(), vertex.z(),
                    texture.x(), texture.y(),
                    normal.x(), normal.y(), normal.z()
                    );
            
            return std::string(buffer);
        }
        
        static TexturedColoredVertex average(const TexturedColoredVertex &a, const TexturedColoredVertex &b)
        {
            TexturedColoredVertex ret;
            
            ret.vertex = (a.vertex + b.vertex) / 2.0f;
            
            float x = (a.color.x() + b.color.x()) / 2.0f;
            float y = (a.color.y() + b.color.y()) / 2.0f;
            float z = (a.color.z() + b.color.z()) / 2.0f;
            float w = (a.color.w() + b.color.w()) / 2.0f;
            
            ret.color = btVector4(x, y, z, w);
            ret.texture = (a.texture + b.texture) / 2.0f;
            ret.normal = (a.normal + b.normal) / 2.0f;
            ret.tangent = (a.tangent + b.tangent) / 2.0f;
            ret.bitangent = (a.vertex + b.bitangent) / 2.0f;
            
            //            ret.vertex.setW(1.0);
            ret.color.setW(1.0);
            
            if(ret.normal.length2() > 0.0)
                ret.normal.normalize();
            if(ret.tangent.length2() > 0.0)
                ret.tangent.normalize();
            if(ret.bitangent.length2() > 0.0)
                ret.bitangent.normalize();
            
            return ret;
        }
        
    };
    
    class ShaderProgram;
    class Camera;
    class Node;
    class LevelOfDetail;
    class PhysicsShape;
    class Image;
    class Material;
    
    ATTRIBUTE_ALIGNED16(class)
    Geometry : public AbstractFactoryObject
    {
        friend class WorldFactory;
        friend class Node;
        friend class Scene;
        friend class PhysicsBodyRigid;
    
      protected:
        Geometry();
        Geometry(const AbstractBuilder &);
        Geometry(const Geometry &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~Geometry();
        Geometry &operator=(const Geometry &);
    
      public:
        using AbstractDecorator::setName;
        using AbstractDecorator::getName;
        using AbstractDecorator::getUuid;
        using AbstractFactoryObject::create;
        //    using AbstractFactoryObject::clone;
        using AbstractFactoryObject::getPointer;
        using AbstractFactoryObject::getPointerValue;
        using AbstractFactoryObject::serializeObject;
    
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual s32 calculateSerializeBufferSize() const;
    
        /**
         *  @author James Folk, 16-02-11 15:02:57
         *
         *  @brief <#Description#>
         *
         *  @param dataBuffer   <#dataBuffer description#>
         *  @param btSerializer <#btSerializer description#>
         */
        virtual void serialize(void *dataBuffer, btSerializer *) const;
    
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual const char *getClassName() const;
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual s32 getType() const;
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        operator std::string() const;
    
        /**
         *  <#Description#>
         *
         *  @param type <#type description#>
         *
         *  @return <#return value description#>
         */
        static Geometry *create(u32 type);
        
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(Geometry * object);
        
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(Geometry & object, lua_State * L, int stack_index);
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
    
    public:
        friend class Node;
        friend class Scene;
    public:
        void setBlendSource(s32 source);
        void setBlendDestination(s32 dest);
        
        void enableBlend(const bool enable = true);
        void enableDepthTest(const bool enable = true);
        void enableStencilTest(const bool enable = true);
        
    public:
        enum MeshType
        {
            MeshType_Obj
        };
        
//        Geometry();
//        Geometry(const Geometry &rhs);
//        const Geometry &operator=(const Geometry &rhs);
//        virtual ~Geometry();
        
        virtual void load(ShaderProgram *shader, const std::string &filecontent="", unsigned int numInstances = 1, unsigned int numSubDivisions = 1);
        void unLoad();
        bool isLoaded()const;
        
        ShaderProgram *const getShader();
        
        void setShaderProgram(ShaderProgram *const shader);
        
        void render(Camera *camera);
        
        virtual void subdivide() = 0;
        
        virtual bool isMaxSubdivisions() = 0;
        
        inline void setVerticeTransform(const GLsizei instanceIdx, const GLsizei verticeIdx, const btTransform &t)
        {
            if(instanceIdx < maxNumberOfInstances() &&
               verticeIdx < numberOfVertices())
            {
                GLsizei idx = (instanceIdx * numberOfVertices());
                idx += (verticeIdx * 16);
                
                t.getOpenGLMatrix(m_MatrixBufferFullSize);
                memcpy(m_ModelViewTransformData + idx,
                       m_MatrixBufferFullSize,
                       sizeof(TRANSFORM_IDENTITY_MATRIX));
                enableModelViewBufferChanged();
            }
        }
        
        inline bool getVerticeTransform(const GLsizei instanceIdx, const GLsizei verticeIdx, btTransform &t)const
        {
            if(instanceIdx < maxNumberOfInstances() &&
               verticeIdx < numberOfVertices())
            {
                GLsizei idx = (instanceIdx * numberOfVertices());
                idx += (verticeIdx * 16);
                
                memcpy(m_MatrixBufferFullSize,
                       m_ModelViewTransformData + idx,
                       sizeof(TRANSFORM_IDENTITY_MATRIX));
                t.setFromOpenGLMatrix(m_MatrixBufferFullSize);
                return true;
            }
            
            return false;
        }
        
        inline void transformVertice(const GLsizei instanceIdx, const GLsizei verticeIdx, const btTransform &t)
        {
            btTransform ret(btTransform::getIdentity());
            
            if(getVerticeTransform(instanceIdx, verticeIdx, ret))
            {
                setVerticeTransform(instanceIdx, verticeIdx, ret * t);
            }
        }
        
        virtual btVector3 getVertexPosition(const GLsizei instanceIdx, const GLsizei verticeIdx)const = 0;
        virtual btVector4 getVertexColor(const GLsizei instanceIdx, const GLsizei verticeIdx)const = 0;
        virtual btVector2 getVertexTexture(const GLsizei instanceIdx, const GLsizei verticeIdx)const = 0;
        virtual btVector3 getVertexNormal(const GLsizei instanceIdx, const GLsizei verticeIdx)const = 0;
        virtual btVector3 getVertexTangent(const GLsizei instanceIdx, const GLsizei verticeIdx)const = 0;
        virtual btVector3 getVertexBitangent(const GLsizei instanceIdx, const GLsizei verticeIdx)const = 0;
        
        virtual void setVertexPosition(const btVector3 &v, const GLsizei instanceIdx, const GLsizei verticeIdx) = 0;
        virtual void setVertexColor(const btVector4 &v, const GLsizei instanceIdx, const GLsizei verticeIdx) = 0;
        virtual void setVertexTexture(const btVector2 &v, const GLsizei instanceIdx, const GLsizei verticeIdx) = 0;
        virtual void setVertexNormal(const btVector3 &v, const GLsizei instanceIdx, const GLsizei verticeIdx) = 0;
        virtual void setVertexTangent(const btVector3 &v, const GLsizei instanceIdx, const GLsizei verticeIdx) = 0;
        virtual void setVertexBitangent(const btVector3 &v, const GLsizei instanceIdx, const GLsizei verticeIdx) = 0;
        
        virtual TexturedColoredVertex getVertex(const GLsizei instanceIdx, const GLsizei verticeIdx)const = 0;
        virtual void setVertex(const TexturedColoredVertex &tcv, const GLsizei instanceIdx, const GLsizei verticeIdx) = 0;
        
        virtual GLsizei numberOfVertices()const = 0;
        virtual GLsizei numberOfIndices()const = 0;
        
        void setRimLightColor(const btVector3 &color);
        const btVector3 &getRimLightColor()const;
        
        void setRimLightStart(const float v);
        float getRimLightStart()const;
        
        void setRimLightEnd(const float v);
        float getRimLightEnd()const;
        
        void setRimLightCoefficient(const float v);
        float getRimLightCoefficient()const;
        
        void setLightSourceAmbientColor(const btVector3 &color);
        const btVector3 &getLightSourceAmbientColor()const;
        
        void setLightSourceDiffuseColor(const btVector3 &color);
        const btVector3 &getLightSourceDiffuseColor()const;
        
        void setLightSourceSpecularColor(const btVector3 &color);
        const btVector3 &getLightSourceSpecularColor()const;
        
        void setLightSourcePosition(const btVector4 &pos);
        const btVector4 &getLightSourcePosition()const;
        
        void setLightSourceSpotDirection(const btVector3 &dir);
        const btVector3 &getLightSourceSpotDirection()const;
        
        void setLightSourceSpotExponent(const float v);
        float getLightSourceSpotExponent()const;
        
        void setLightSourceSpotCutoff(const float v);
        float getLightSourceSpotCutoff()const;
        
        void setLightSourceSpotCosCutoff(const float v);
        float getLightSourceSpotCosCutoff()const;
        
        void setLightSourceConstantAttenuation(const float v);
        float getLightSourceConstantAttenuation()const;
        
        void setLightSourceLinearAttenuation(const float v);
        float getLightSourceLinearAttenuation()const;
        
        void setLightSourceQuadraticAttenuation(const float v);
        float getLightSourceQuadraticAttenuation()const;
        
        void setLightAmbientColor(const btVector3 &color);
        const btVector3 &getLightAmbientColor()const;
        
        void setMaterialShininess(const float v);
        float getMaterialShininess()const;
        
        void setFogMaxDistance(const float v);
        float getFogMaxDistance()const;
        
        void setFogMinDistance(const float v);
        float getFogMinDistance()const;
        
        void setFogColor(const btVector3 &color);
        const btVector3 &getFogColor()const;
        
        void setFogDensity(const float v);
        float getFogDensity()const;
        
        void setAmbientTexture(const GLuint t);
        void setDiffuseTexture(const GLuint t);
        void setNormalTexture(const GLuint t);
        void setSpecularTexture(const GLuint t);
        
        virtual void setOpacity(Node *node) = 0;
        virtual void setHidden(Node *node, bool hidden = true) = 0;
        virtual void setColorBase(Node *node) = 0;
        
        void hide(Camera * camera);
        void show(Camera * camera);
        bool isHidden(Camera * camera) const;
        
        Node *getParent();
        const Node *getParent() const;
    protected:
        
        const void *getModelViewTransformArrayBufferPtr()const;
        GLsizeiptr getModelViewTransformArrayBufferSize()const;
        bool isModelViewBufferChanged()const;
        void enableModelViewBufferChanged(bool changed = true);
        
        const void *getNormalMatrixTransformArrayBufferPtr()const;
        GLsizeiptr getNormalMatrixTransformArrayBufferSize()const;
        bool isNormalMatrixBufferChanged()const;
        void enableNormalMatrixBufferChanged(bool changed = true);
        
        virtual void loadData();
        virtual void unLoadData();
        
        virtual const void *getVertexArrayBufferPtr()const = 0;
        virtual GLsizeiptr getVertexArrayBufferSize()const = 0;
        bool isVertexArrayBufferChanged()const;
        void enableVertexArrayBufferChanged(bool changed = true);
        
        virtual const void *getElementArrayBufferPtr()const = 0;
        virtual GLsizeiptr getElementArrayBufferSize()const = 0;
        bool isIndiceArrayBufferChanged()const;
        void enableIndiceArrayBufferChanged(bool changed = true);
        
        virtual GLenum getElementIndexType()const = 0;
        
        
        
        void addReference(Node *node);
        void removeReference(Node *node);
        
        void setTransform(const unsigned long index, const btTransform &transform);
        btTransform getTransform(const unsigned long index);
        
        void setNormalMatrixTransform(const unsigned long index, const btTransform &transform);
        btTransform getNormalMatrixTransform(const unsigned long index);
        
        
        
        virtual void applyShape(Node * node, PhysicsShape *physicsShape) = 0;
        virtual bool shouldApplyShape(Node * node) const = 0;
        
        virtual void transformVertices(Node * node, const btTransform &transfrom) = 0;
        virtual void transformVertexColors(Node * node, const btTransform &transform) = 0;
        virtual void transformTextureCoordinates(Node * node, const btTransform &transform) = 0;
        
        
        virtual GLsizei maxNumberOfInstances()const;
        virtual GLsizei maxNumberOfSubDivisions()const;
        virtual GLsizei subdivisionBufferSize()const;
        
        unsigned long getGeometryIndex(Node *const node)const;
        
        GLfloat *m_MatrixBuffer;
        float *m_MatrixBufferFullSize;
        
        GLfloat *m_ModelViewTransformData;
        GLfloat *m_NormalMatrixTransformData;
        
    private:
        GLuint m_VertexArray;
        GLuint m_ModelViewBuffer;
        GLuint m_NormalMatrixTransformBuffer;
        GLuint m_VerticesBuffer;
        GLuint m_IndexBuffer;
        
        std::vector<bool> m_References;
        GLsizei m_NumberInstances;
        GLsizei m_NumberSubDivisions;
        GLsizei m_ExtraSubdivisionBuffer;
        
        ShaderProgram *m_Shader;
        
        bool m_OpacityModifyRGB;
        bool m_ElementBufferChanged;
        bool m_VertexBufferChanged;
        bool m_NormalMatrixBufferChanged;
        bool m_ModelViewBufferChanged;
        bool m_ShaderChanged;
        
        bool m_HasPositionAttrib;
        bool m_HasTexCoordAttrib;
        bool m_HasNormalAttrib;
        bool m_HasColorAttrib;
        bool m_HasTangentAttrib;
        bool m_HasBiTangentAttrib;
        
        btVector3 m_RimLightColor;
        float m_RimLightStart;
        float m_RimLightEnd;
        float m_RimLightCoefficient;
        btVector3 m_LightSourceAmbientColor;
        btVector3 m_LightSourceDiffuseColor;
        btVector3 m_LightSourceSpecularColor;
        btVector4 m_LightSourcePosition_worldspace;
        btVector3 m_LightSourceSpotDirection;
        float m_LightSourceSpotExponent;
        float m_LightSourceSpotCutoff;
        float m_LightSourceSpotCosCutoff;
        float m_LightSourceConstantAttenuation;
        float m_LightSourceLinearAttenuation;
        float m_LightSourceQuadraticAttenuation;
        btVector3 m_LightAmbientColor;
        float m_MaterialShininess;
        float m_FogMaxDistance;
        float m_FogMinDistance;
        btVector3 m_FogColor;
        float m_FogDensity;
        
        GLuint m_AmbientTexture;
        GLuint m_DiffuseTexture;
        GLuint m_NormalTexture;
        GLuint m_SpecularTexture;
        
        s32 m_blendFuncSource;
        s32 m_blendFuncDestination;
    
        bool m_enableBlend;
        bool m_enableDepthTest;
        bool m_enableStencilTest;
        
        Material *m_Material;
        njliBitCategories m_RenderCategory;
    public:
        void setMaterial(Material * material, Image *image = NULL);
        
        void removeMaterial();
        Material *getMaterial();
        const Material *getMaterial() const;
    };
}

#endif /* Geometry_hpp */


////
////  Geometry.h
////  JLIGameEngineTest
////
////  Created by James Folk on 11/22/14.
////  Copyright (c) 2014 James Folk. All rights reserved.
////
//
//#ifndef __JLIGameEngineTest__Geometry__
//#define __JLIGameEngineTest__Geometry__
//
//#include "AbstractBuilder.h"
//#include "AbstractFactoryObject.h"
//#include "lua.hpp"
//
//#include <bitset>
//#include <string>
//
//#include "JLIFactoryTypes.h"
//#include "btVector2.h"
//#include "btVector3.h"
//
//class btTransform;
//
//#define NUMBER_OF_MESHES (5000)
//
//namespace njli
//{
//  class GeometryBuilder;
//  class LevelOfDetail;
//  class Material;
//  class ShaderProgram;
//  class Camera;
//  class PhysicsShape;
//  class Node;
//  class Image;
//
//  /**
//       *  <#Description#>
//       */
//  ATTRIBUTE_ALIGNED16(class)
//  Geometry : public AbstractFactoryObject
//  {
//    friend class WorldFactory;
//    friend class Node;
//    friend class Scene;
//    friend class PhysicsBodyRigid;
//
//  protected:
//    Geometry();
//    Geometry(const AbstractBuilder &);
//    Geometry(const Geometry &);
//    BT_DECLARE_ALIGNED_ALLOCATOR();
//    virtual ~Geometry();
//    Geometry &operator=(const Geometry &);
//
//  public:
//    using AbstractDecorator::setName;
//    using AbstractDecorator::getName;
//    using AbstractFactoryObject::create;
//    //    using AbstractFactoryObject::clone;
//    using AbstractFactoryObject::getPointer;
//    using AbstractFactoryObject::getPointerValue;
//    using AbstractFactoryObject::serializeObject;
//
//    /**
//         *  <#Description#>
//         *
//         *  @return <#return value description#>
//         */
//    virtual s32 calculateSerializeBufferSize() const;
//
//    /**
//         *  @author James Folk, 16-02-11 15:02:57
//         *
//         *  @brief <#Description#>
//         *
//         *  @param dataBuffer   <#dataBuffer description#>
//         *  @param btSerializer <#btSerializer description#>
//         */
//    virtual void serialize(void *dataBuffer, btSerializer *) const;
//
//    /**
//         *  <#Description#>
//         *
//         *  @return <#return value description#>
//         */
//    virtual const char *getClassName() const;
//    /**
//         *  <#Description#>
//         *
//         *  @return <#return value description#>
//         */
//    virtual s32 getType() const;
//    /**
//         *  <#Description#>
//         *
//         *  @return <#return value description#>
//         */
//    operator std::string() const;
//
//    /**
//         *  <#Description#>
//         *
//         *  @param type <#type description#>
//         *
//         *  @return <#return value description#>
//         */
//    static Geometry *create(u32 type);
//    /**
//         *  <#Description#>
//         *
//         *  @param object <#object description#>
//         */
//    static void destroy(Geometry * object);
//    /**
//         *  <#Description#>
//         *
//         *  @param object      <#object description#>
//         *  @param L           <#L description#>
//         *  @param stack_index <#stack_index description#>
//         */
//    static void load(Geometry & object, lua_State * L, int stack_index);
//    /**
//         *  <#Description#>
//         *
//         *  @return <#return value description#>
//         */
//    static u32 type();
//
//  public:
//    // TODO: fill in specific methods for Geometry
//
//    /**
//         *  <#Description#>
//         *
//         *  @param geometry <#geometry description#>
//         */
//    void addLevelOfDetail(LevelOfDetail * geometry);
//    /**
//         *  <#Description#>
//         *
//         *  @param geometry <#geometry description#>
//         *
//         *  @return <#return value description#>
//         */
//    bool removeLevelOfDetail(LevelOfDetail * geometry);
//    /**
//         *  <#Description#>
//         */
//    void removeAllLevelOfDetails();
//    /**
//         *  <#Description#>
//         *
//         *  @param geometries <#geometries description#>
//         */
//    void getLevelOfDetails(std::vector<LevelOfDetail *> & geometries) const;
//    /**
//         *  <#Description#>
//         *
//         *  @param index <#index description#>
//         *
//         *  @return <#return value description#>
//         */
//    LevelOfDetail *getLevelOfDetail(const u32 index);
//    /**
//         *  <#Description#>
//         *
//         *  @param index <#index description#>
//         *
//         *  @return <#return value description#>
//         */
//    const LevelOfDetail *getLevelOfDetail(const u32 index) const;
//
//    /**
//         *  <#Description#>
//         *
//         *  @param material <#material description#>
//         */
//    void setMaterial(Material * material, Image *image = NULL);
//    /**
//         *  <#Description#>
//         */
//    void removeMaterial();
//    /**
//         *  <#Description#>
//         *
//         *  @return <#return value description#>
//         */
//    Material *getMaterial();
//    /**
//         *  <#Description#>
//         *
//         *  @return <#return value description#>
//         */
//    const Material *getMaterial() const;
//
//    /**
//         *  <#Description#>
//         *
//         *  @param shader <#shader description#>
//         */
//    void setShaderProgram(ShaderProgram * shader);
//    /**
//         *  <#Description#>
//         */
//    void removeShaderProgram();
//    /**
//         *  <#Description#>
//         *
//         *  @return <#return value description#>
//         */
//    ShaderProgram *getShaderProgram();
//    /**
//         *  <#Description#>
//         *
//         *  @return <#return value description#>
//         */
//    const ShaderProgram *getShaderProgram() const;
//
//    /**
//         *  <#Description#>
//         *
//         *  @return <#return value description#>
//         */
//    u32 getMaxMeshes() const;
//
//    /**
//         *  @author James Folk, 16-02-11 17:02:44
//         *
//         *  @brief <#Description#>
//         *
//         *  @param geometry <#geometry description#>
//         *  @param vertices <#vertices description#>
//         *  @param node     <#node description#>
//         */
//    virtual void getVertices(LevelOfDetail * geometry, btVector3 * *vertices,
//                             Node * node) const = 0;
//
//    /**
//         *  @author James Folk, 16-02-11 17:02:49
//         *
//         *  @brief <#Description#>
//         *
//         *  @param geometry <#geometry description#>
//         *  @param node     <#node description#>
//         *
//         *  @return <#return value description#>
//         */
//    virtual u64 getNumberOfVertices(LevelOfDetail * geometry, Node * node)
//        const = 0;
//
//    /**
//         *  @author James Folk, 16-02-11 17:02:56
//         *
//         *  @brief <#Description#>
//         *
//         *  @param geometry      <#geometry description#>
//         *  @param colorVertices <#colorVertices description#>
//         *  @param node          <#node description#>
//         */
//    virtual void getVertexColors(LevelOfDetail * geometry,
//                                 btVector4 * *colorVertices, Node * node)
//        const = 0;
//
//    /**
//         *  @author James Folk, 16-02-11 17:02:05
//         *
//         *  @brief <#Description#>
//         *
//         *  @param geometry <#geometry description#>
//         *  @param node     <#node description#>
//         *
//         *  @return <#return value description#>
//         */
//    virtual u64 getNumberOfVertexColors(LevelOfDetail * geometry, Node * node)
//        const = 0;
//
//    /**
//         *  @author James Folk, 16-02-11 17:02:14
//         *
//         *  @brief <#Description#>
//         *
//         *  @param geometry           <#geometry description#>
//         *  @param textureCoordinates <#textureCoordinates description#>
//         *  @param node               <#node description#>
//         */
//    virtual void getTextureCoordinates(LevelOfDetail * geometry,
//                                       btVector2 * *textureCoordinates,
//                                       Node * node) const = 0;
//
//    /**
//         *  @author James Folk, 16-02-11 17:02:21
//         *
//         *  @brief <#Description#>
//         *
//         *  @param geometry <#geometry description#>
//         *  @param node     <#node description#>
//         *
//         *  @return <#return value description#>
//         */
//    virtual u64 getNumberOfTextureCoordinates(LevelOfDetail * geometry,
//                                              Node * node) const = 0;
//
//    /**
//         *  <#Description#>
//         *
//         *  @param node    <#node description#>
//         *  @param opacity <#opacity description#>
//         */
//    virtual void setOpacity(Node * node, f32 opacity) = 0;
//    /**
//         *  <#Description#>
//         *
//         *  @param node      <#node description#>
//         *  @param transfrom <#transfrom description#>
//         */
//
//    /**
//         *  <#Description#>
//         *
//         *  @param node    <#node description#>
//         *  @param opacity <#opacity description#>
//         */
//    virtual void setHidden(Node * node, bool hidden = true) = 0;
//
//    /**
//     <#Description#>
//
//     @param node <#node description#>
//     @param camera <#camera description#>
//     */
//    //    virtual void setHidden(Node * node, Camera * camera);
//
//    /**
//         *  <#Description#>
//         *
//         *  @param node    <#node description#>
//         *  @param opacity <#opacity description#>
//         */
//    virtual bool isHidden(Node * node) const = 0;
//
//    virtual void transformVertices(Node * node,
//                                   const btTransform &transfrom) = 0;
//    /**
//         *  <#Description#>
//         *
//         *  @param node      <#node description#>
//         *  @param transform <#transform description#>
//         */
//    virtual void transformVertexColors(Node * node,
//                                       const btTransform &transform) = 0;
//    /**
//         *  <#Description#>
//         *
//         *  @param node      <#node description#>
//         *  @param transform <#transform description#>
//         */
//    virtual void transformTextureCoordinates(Node * node,
//                                             const btTransform &transform) = 0;
//    /**
//         *  <#Description#>
//         *
//         *  @param node         <#node description#>
//         *  @param physicsShape <#physicsShape description#>
//         */
//    virtual void applyShape(Node * node, PhysicsShape * physicsShape) = 0;
//
//    virtual bool shouldApplyShape(Node * node) const = 0;
//    /**
//         *  <#Description#>
//         *
//         *  @return <#return value description#>
//         */
//    virtual s32 numberOfVertices() const = 0;
//    /**
//         *  <#Description#>
//         *
//         *  @return <#return value description#>
//         */
//    virtual s32 numberOfIndices() const = 0;
//
//    /**
//         *  <#Description#>
//         *
//         *  @return <#return value description#>
//         */
//    virtual const void *getArrayBuffer() const = 0;
//    /**
//         *  <#Description#>
//         *
//         *  @return <#return value description#>
//         */
//    virtual s64 getArrayBufferSize() const = 0;
//
//    /**
//         *  <#Description#>
//         *
//         *  @return <#return value description#>
//         */
//    virtual const void *getElementArrayBuffer() const = 0;
//    /**
//         *  <#Description#>
//         *
//         *  @return <#return value description#>
//         */
//    virtual s64 getElementArrayBufferSize() const = 0;
//
//    virtual void setSize(Node * node, const btVector3 &position,
//                         const f32 halfSize) = 0;
//    virtual void setColor(Node * node, const btVector4 &color) = 0;
//
//    void setBlendSource(s32 source);
//    void setBlendDestination(s32 dest);
//    void setupOpacity(Material * material, Image * image);
//
//    /**
//         *  <#Description#>
//         */
//    virtual void loadGPU();
//    /**
//         *  <#Description#>
//         */
//    virtual void unLoadGPU();
//    /**
//         *  <#Description#>
//         *
//         *  @return <#return value description#>
//         */
//    virtual bool isLoadedGPU() const;
//
//    /**
//         *  <#Description#>
//         *
//         *  @param index     <#index description#>
//         *  @param transform <#transform description#>
//         */
//    virtual void setTransform(const u64 index, const btTransform &transform);
//    /**
//         *  <#Description#>
//         *
//         *  @param index <#index description#>
//         *
//         *  @return <#return value description#>
//         */
//    virtual btTransform getTransform(const u64 index);
//
//    /**
//     *  <#Description#>
//     *
//     *  @param index     <#index description#>
//     *  @param transform <#transform description#>
//     */
//    virtual void setColorTransform(const u64 index,
//                                   const btTransform &transform);
//    /**
//     *  <#Description#>
//     *
//     *  @param index <#index description#>
//     *
//     *  @return <#return value description#>
//     */
//    virtual btTransform getColorTransform(const u64 index);
//
//    virtual void getAabb(Node * node, btVector3 & aabbMin, btVector3 & aabbMax)
//        const;
//
//    void enableBlend(const bool enable = true);
//    void enableDepthTest(const bool enable = true);
//    void enableStencilTest(const bool enable = true);
//
//    void hide(Camera * camera);
//    void show(Camera * camera);
//    bool isHidden(Camera * camera) const;
//
//  protected:
//    virtual void load();
//    virtual void unLoad();
//    virtual void render(Camera * camera, s32 mode = 0x0004);
//
//    //        virtual void setupShader();
//
//    Node *getParent();
//    const Node *getParent() const;
//
//    void addReference(Node *);
//    void removeReference(Node *);
//    virtual void hideGeometry(Node *) = 0;
//
//    void enableBufferModified(bool modified = true);
//    bool isBufferModified() const;
//
//  public:
//    static void setPointSize(const f32 size);
//    static f32 getPointSize();
//    static void setLineWidth(const f32 size);
//    static f32 getLineWidth();
//
//    s32 numberOfReferences() const;
//    ATTRIBUTE_ALIGNED16(struct)
//    TexturedColoredVertex
//    {
//      TexturedColoredVertex()
//          : vertex(0, 0, 0), color(1, 1, 1, 1), texture(0, 0), opacity(1.0f),
//            hidden(0.0f)
//      {
//      }
//      TexturedColoredVertex(const btVector3 &vertex, const btVector4 &color,
//                            const btVector2 &texture, const f32 opacity,
//                            const f32 hidden)
//          : vertex(vertex), color(color), texture(texture), opacity(opacity),
//            hidden(hidden)
//      {
//      }
//      btVector3 vertex;
//      btVector4 color;
//      btVector2 texture;
//      f32 opacity;
//      f32 hidden;
//
//      operator std::string() const
//      {
//        char buffer[2048];
//        sprintf(buffer, "{{%f, %f, %f}, {%f, %f}, {%f, %f, %f, %f}}",
//                vertex.x(), vertex.y(), vertex.z(), texture.x(), texture.y(),
//                color.x(), color.y(), color.z(), color.w());
//        return std::string(buffer);
//      }
//
//      TexturedColoredVertex &operator=(const TexturedColoredVertex &rhs)
//      {
//        if (this != &rhs)
//          {
//            vertex = rhs.vertex;
//            color = rhs.color;
//            texture = rhs.texture;
//            opacity = rhs.opacity;
//            hidden = rhs.hidden;
//          }
//        return *this;
//      }
//    };
//
//    ATTRIBUTE_ALIGNED16(struct)
//    TexturedNormaledColoredVertex
//    {
//      btVector3 vertex;
//      btVector3 normal;
//      btVector2 texture;
//      btVector4 color;
//
//      operator std::string() const
//      {
//        char buffer[2048];
//        sprintf(buffer,
//                "{{%f, %f, %f}, {%f, %f, %f}, {%f, %f}, {%f, %f, %f, %f}}",
//                vertex.x(), vertex.y(), vertex.z(), normal.x(), normal.y(),
//                normal.z(), texture.x(), texture.y(), color.x(), color.y(),
//                color.z(), color.w());
//        return std::string(buffer);
//      }
//    };
//
//    void sort(const btVector3 &cameraOrigin);
//
//    void setupShader();
//
//  private:
//    void quickSort(signed long left, signed long right,
//                   const btVector3 &cameraOrigin);
//
//    void swapTransformData(const size_t idx1, const size_t idx2);
//    bool lessThan(const size_t idx1, const size_t idx2,
//                  const btVector3 &cameraOrigin);
//    bool greaterThan(const size_t idx1, const size_t idx2,
//                     const btVector3 &cameraOrigin);
//
//    virtual void swapVertexData(const size_t idx1, const size_t idx2) = 0;
//
//    void bindTransform();
//    void bindColorTransform();
//    std::vector<LevelOfDetail *> m_LevelOfDetailList;
//
//    Material *m_Material;
//    ShaderProgram *m_ShaderProgram;
//    u32 m_projectionMatrixUniform;
//    //    u32 m_modelViewMatrixUniform;
//    u32 m_modelViewBufferID;
//    u32 m_colorTransformBufferID;
//    f32 *m_ModelviewTransform;
//    f32 *m_ColorTransform;
//
//    u32 m_InTransformAttrib;
//    u32 m_InColorTransform;
//    u32 m_verticesBufferID;
//    u32 indexBufferID;
//    u32 m_vertexArrayID;
//
//    u32 m_InPositionAttrib;
//    u32 m_InTexCoordAttrib;
//    u32 m_InColorAttrib;
//    u32 m_InOpacityAttrib;
//    u32 m_InHiddenAttrib;
//
//    std::bitset<NUMBER_OF_MESHES> m_References;
//
//    static f32 s_PointSize;
//
//    s32 m_blendFuncSource;
//    s32 m_blendFuncDestination;
//    bool _opacityModifyRGB;
//    //    u32 u_opacityModifyRGB;
//    u32 u_pointSize;
//
//    bool m_enableBlend;
//    bool m_enableDepthTest;
//    bool m_enableStencilTest;
//
//    bool m_TransformDirty;
//    bool m_ColorTransformDirty;
//    // u64 m_StartCopyTransform;
//
//    bool m_LoadGPU;
//    void loadGPU_Internal();
//
//    static f32 s_LineWidth;
//
//    void setupOpacity_Internal(Material * material, Image * image);
//    Material *m_setupOpacity_Material;
//    Image *m_setupOpacity_Image;
//    bool m_setupOpacity;
//
//    bool m_UnLoadGPU;
//    void unLoadGPU_Internal();
//
//    // bool m_setupShader;
//
//    bool m_bufferModified;
//    bool m_vertexAttribChanged;
//
//    float *m_MatrixBuffer;
//    u64 m_maxindice;
//    njliBitCategories m_RenderCategory;
//  };
//}
//
//#endif /* defined(__JLIGameEngineTest__Geometry__) */
