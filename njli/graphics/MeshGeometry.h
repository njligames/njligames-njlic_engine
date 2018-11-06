//
//  MeshGeometry.hpp
//  TeapotExplosion
//
//  Created by James Folk on 12/8/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#ifndef MeshGeometry_hpp
#define MeshGeometry_hpp

#include "Geometry.h"
#include "MeshGeometryBuilder.h"

namespace njli
{
    ATTRIBUTE_ALIGNED16(class) MeshGeometry : public Geometry
    {
        friend class WorldFactory;
    protected:
        MeshGeometry();
        MeshGeometry(const AbstractBuilder &);
        MeshGeometry(const MeshGeometry &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~MeshGeometry();
        MeshGeometry &operator=(const MeshGeometry &);
        
    public:
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual s32 calculateSerializeBufferSize() const;
        /**
         *  <#Description#>
         *
         *  @param btSerializer <#btSerializer description#>
         */
        virtual void serialize(void *, btSerializer *) const;
        
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
         *  @param size <#size description#>
         *
         *  @return <#return value description#>
         */
        static MeshGeometry **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(MeshGeometry * *array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static MeshGeometry *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static MeshGeometry *create(const MeshGeometryBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static MeshGeometry *clone(const MeshGeometry &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static MeshGeometry *copy(const MeshGeometry &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(MeshGeometry * object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(MeshGeometry & object, lua_State * L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
        
    public:
        
        
        void load(ShaderProgram *shader, const std::string &filecontent, unsigned int numInstances, unsigned int numSubDivisions);
        
        void subdivide();
        bool isMaxSubdivisions();
        
        btVector3 getVertexPosition(const GLsizei instanceIdx, const GLsizei verticeIdx)const;
        btVector4 getVertexColor(const GLsizei instanceIdx, const GLsizei verticeIdx)const;
        btVector2 getVertexTexture(const GLsizei instanceIdx, const GLsizei verticeIdx)const;
        btVector3 getVertexNormal(const GLsizei instanceIdx, const GLsizei verticeIdx)const;
        btVector3 getVertexTangent(const GLsizei instanceIdx, const GLsizei verticeIdx)const;
        btVector3 getVertexBitangent(const GLsizei instanceIdx, const GLsizei verticeIdx)const;
        
        void setVertexPosition(const btVector3 &v, const GLsizei instanceIdx, const GLsizei verticeIdx);
        void setVertexColor(const btVector4 &v, const GLsizei instanceIdx, const GLsizei verticeIdx);
        void setVertexTexture(const btVector2 &v, const GLsizei instanceIdx, const GLsizei verticeIdx);
        void setVertexNormal(const btVector3 &v, const GLsizei instanceIdx, const GLsizei verticeIdx);
        void setVertexTangent(const btVector3 &v, const GLsizei instanceIdx, const GLsizei verticeIdx);
        void setVertexBitangent(const btVector3 &v, const GLsizei instanceIdx, const GLsizei verticeIdx);
        
        virtual TexturedColoredVertex getVertex(const GLsizei instanceIdx, const GLsizei verticeIdx)const;
        virtual void setVertex(const TexturedColoredVertex &tcv, const GLsizei instanceIdx, const GLsizei verticeIdx);
        
        virtual GLsizei numberOfVertices()const;
        virtual GLsizei numberOfIndices()const;
    protected:
        void subdivideTriangle(const TexturedColoredVertex &p0,
            const TexturedColoredVertex &p1,
            const TexturedColoredVertex &p2,
                               TexturedColoredVertex *triangleBuffer,
                               GLsizei newIndiceStart,
                               GLuint *indiceBuffer);
        
        virtual void loadData();
        virtual void unLoadData();
        
        virtual const void *getVertexArrayBufferPtr()const;
        virtual GLsizeiptr getVertexArrayBufferSize()const;
        
        virtual const void *getElementArrayBufferPtr()const;
        virtual GLsizeiptr getElementArrayBufferSize()const;
        
        virtual GLenum getElementIndexType()const;
        
        virtual void setOpacity(Node *node);
        virtual void setHidden(Node *node, bool hidden = true);
        virtual void setColorBase(Node *node);
        
        virtual void applyShape(Node * node, PhysicsShape * physicsShape);
        virtual bool shouldApplyShape(Node * node) const;
        
        virtual void transformVertices(Node * node, const btTransform &transfrom);
        virtual void transformVertexColors(Node * node, const btTransform &transform);
        virtual void transformTextureCoordinates(Node * node, const btTransform &transform);
        
    private:
        TexturedColoredVertex *m_VertexData;
        GLuint *m_IndiceData;
        
        TexturedColoredVertex *m_VertexDataBuffer;
        GLuint *m_IndiceDataBuffer;
        
        std::string m_Filedata;
        GLsizei m_NumberOfVertices;
        GLsizei m_NumberOfIndices;
        GLsizei m_TotalSubdivisions;
        
        TexturedColoredVertex *m_triangleBuffer;
        GLuint *m_indiceBuffer;
        
    };
}

#endif /* MeshGeometry_hpp */
