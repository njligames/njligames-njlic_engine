//
//  MeshGeometry.cpp
//  TeapotExplosion
//
//  Created by James Folk on 12/8/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#include "MeshGeometry.h"

#include "Node.h"
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "World.h"

#include "Log.h"
#define TAG "Cube.cpp"
#define FORMATSTRING "{\"njli::MeshGeometry\":[]}"
#include "JsonJLI.h"
#include "btPrint.h"

namespace njli
{
    MeshGeometry::MeshGeometry()
        : Geometry(), m_VertexData(NULL), m_IndiceData(NULL),
          m_VertexDataBuffer(NULL), m_IndiceDataBuffer(NULL), m_Filedata(""),
          m_NumberOfVertices(0), m_NumberOfIndices(0), m_TotalSubdivisions(0),
          m_triangleBuffer(new TexturedColoredVertex[12]),
          m_indiceBuffer(new GLuint[12])
    {
    }

    MeshGeometry::MeshGeometry(const AbstractBuilder &builder) {}

    MeshGeometry::MeshGeometry(const MeshGeometry &copy) {}

    MeshGeometry::~MeshGeometry()
    {
        delete[] m_indiceBuffer;
        m_indiceBuffer = NULL;

        delete[] m_triangleBuffer;
        m_triangleBuffer = NULL;

        if (m_IndiceDataBuffer)
            delete[] m_IndiceDataBuffer;
        m_IndiceDataBuffer = NULL;

        if (m_VertexDataBuffer)
            delete[] m_VertexDataBuffer;
        m_VertexDataBuffer = NULL;

        if (m_IndiceData)
            delete[] m_IndiceData;
        m_IndiceData = NULL;

        if (m_VertexData)
            delete[] m_VertexData;
        m_VertexData = NULL;
    }

    MeshGeometry &MeshGeometry::operator=(const MeshGeometry &)
    {
        return *this;
    }

    s32 MeshGeometry::calculateSerializeBufferSize() const
    {
        // TODO: calculateSerializeBufferSize
        return 0;
    }

    void MeshGeometry::serialize(void *dataBuffer,
                                 btSerializer *serializer) const
    {
        // TODO: serialize
    }

    const char *MeshGeometry::getClassName() const { return "MeshGeometry"; }

    s32 MeshGeometry::getType() const { return MeshGeometry::type(); }

    MeshGeometry::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }

    MeshGeometry **MeshGeometry::createArray(const u32 size)
    {
        return (MeshGeometry **)World::getInstance()
            ->getWorldFactory()
            ->createArray(MeshGeometry::type(), size);
    }

    void MeshGeometry::destroyArray(MeshGeometry **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray(
            (AbstractFactoryObject **)array, size);
    }

    MeshGeometry *MeshGeometry::create()
    {
        return dynamic_cast<MeshGeometry *>(
            World::getInstance()->getWorldFactory()->create(
                MeshGeometry::type()));
    }

    MeshGeometry *MeshGeometry::create(const MeshGeometryBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;

        return dynamic_cast<MeshGeometry *>(
            World::getInstance()->getWorldFactory()->create(*b));
    }

    MeshGeometry *MeshGeometry::clone(const MeshGeometry &object)
    {
        return dynamic_cast<MeshGeometry *>(
            World::getInstance()->getWorldFactory()->clone(object, false));
    }

    MeshGeometry *MeshGeometry::copy(const MeshGeometry &object)
    {
        return dynamic_cast<MeshGeometry *>(
            World::getInstance()->getWorldFactory()->clone(object, true));
    }

    void MeshGeometry::destroy(MeshGeometry *object)
    {
        if (object)
        {
            Geometry::destroy(object);
        }
    }

    void MeshGeometry::load(MeshGeometry &object, lua_State *L, int index)
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
            // stack now contains: -1 => key; -2 => value; -3 => key; -4 =>
            // table
            const char *key = lua_tostring(L, -1);
            //            const char *value = lua_tostring(L, -2);
            if (lua_istable(L, -2))
            {
                MeshGeometry::load(object, L, -2);
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
        // stack now contains: -1 => table (when lua_next returns 0 it pops the
        // key but does not push anything.) Pop table
        lua_pop(L, 1);
        // Stack is now the same as it was on entry to this function
    }

    u32 MeshGeometry::type() { return JLI_OBJECT_TYPE_MeshGeometry; }

    void MeshGeometry::load(ShaderProgram *shader, const std::string &filedata,
                            unsigned int numInstances,
                            unsigned int numSubDivisions)
    {
        m_TotalSubdivisions = 0;
        m_Filedata = filedata;

        Geometry::load(shader, filedata, numInstances, numSubDivisions);
    }

    void MeshGeometry::subdivide()
    {
        if (m_TotalSubdivisions < maxNumberOfSubDivisions())
        {
            GLsizei previousNumberOfIndices = m_NumberOfIndices;

            m_NumberOfVertices *= 4;
            m_NumberOfIndices *= 4;

            for (GLsizei currentIndice = 0, newIndice = 0;
                 currentIndice < previousNumberOfIndices;
                 currentIndice += 3, newIndice += 12)
            {
                subdivideTriangle(m_VertexData[currentIndice + 0],
                                  m_VertexData[currentIndice + 1],
                                  m_VertexData[currentIndice + 2],
                                  m_triangleBuffer, newIndice, m_indiceBuffer);

                memcpy(m_VertexDataBuffer + newIndice, m_triangleBuffer,
                       sizeof(TexturedColoredVertex) * 12);
                memcpy(m_IndiceDataBuffer + newIndice, m_indiceBuffer,
                       sizeof(GLuint) * 12);
            }

            enableVertexArrayBufferChanged(true);
            enableIndiceArrayBufferChanged(true);

            ++m_TotalSubdivisions;

            unsigned long vertexInstanceIndex = 0;
            unsigned long indiceInstanceIndex = 0;
            for (unsigned long meshIndex = 0;
                 meshIndex < maxNumberOfInstances(); meshIndex++)
            {
                memcpy(m_VertexData + vertexInstanceIndex, m_VertexDataBuffer,
                       sizeof(TexturedColoredVertex) * numberOfVertices());
                vertexInstanceIndex += numberOfVertices();

                for (unsigned long indiceIndex = 0;
                     indiceIndex < numberOfIndices(); indiceIndex++)
                {
                    m_IndiceData[indiceInstanceIndex] =
                        m_IndiceDataBuffer[indiceIndex] +
                        (GLuint)((meshIndex * numberOfVertices()));
                    indiceInstanceIndex++;
                }
                //                memcpy(m_IndiceData + indiceInstanceIndex,
                //                       m_IndiceDataBuffer +
                //                       (GLuint)((meshIndex *
                //                       numberOfVertices())), sizeof(GLuint) *
                //                       numberOfIndices());
                //                indiceInstanceIndex += numberOfIndices();
            }

            enableModelViewBufferChanged(true);
            enableNormalMatrixBufferChanged(true);
        }
    }

    bool MeshGeometry::isMaxSubdivisions()
    {
        return m_TotalSubdivisions >= maxNumberOfSubDivisions();
    }

    btVector3 MeshGeometry::getVertexPosition(const GLsizei instanceIdx,
                                              const GLsizei verticeIdx) const
    {
        btVector3 ret(0, 0, 0);

        if (instanceIdx < maxNumberOfInstances() &&
            verticeIdx < numberOfVertices())
        {
            GLsizei idx = (instanceIdx * numberOfVertices());
            idx += (verticeIdx * 1);

            memcpy(m_triangleBuffer, m_VertexData + idx,
                   sizeof(TexturedColoredVertex) * 12);

            ret = m_triangleBuffer[0].vertex;
        }

        return ret;
    }

    btVector4 MeshGeometry::getVertexColor(const GLsizei instanceIdx,
                                           const GLsizei verticeIdx) const
    {
        btVector4 ret(0, 0, 0, 0);

        if (instanceIdx < maxNumberOfInstances() &&
            verticeIdx < numberOfVertices())
        {
            GLsizei idx = (instanceIdx * numberOfVertices());
            idx += (verticeIdx * 1);

            memcpy(m_triangleBuffer, m_VertexData + idx,
                   sizeof(TexturedColoredVertex) * 12);

            ret = m_triangleBuffer[0].color;
        }

        return ret;
    }

    btVector2 MeshGeometry::getVertexTexture(const GLsizei instanceIdx,
                                             const GLsizei verticeIdx) const
    {
        btVector2 ret(0, 0);

        if (instanceIdx < maxNumberOfInstances() &&
            verticeIdx < numberOfVertices())
        {
            GLsizei idx = (instanceIdx * numberOfVertices());
            idx += (verticeIdx * 1);

            memcpy(m_triangleBuffer, m_VertexData + idx,
                   sizeof(TexturedColoredVertex) * 12);

            ret = m_triangleBuffer[0].texture;
        }

        return ret;
    }

    btVector3 MeshGeometry::getVertexNormal(const GLsizei instanceIdx,
                                            const GLsizei verticeIdx) const
    {
        btVector3 ret(0, 0, 0);

        if (instanceIdx < maxNumberOfInstances() &&
            verticeIdx < numberOfVertices())
        {
            GLsizei idx = (instanceIdx * numberOfVertices());
            idx += (verticeIdx * 1);

            memcpy(m_triangleBuffer, m_VertexData + idx,
                   sizeof(TexturedColoredVertex) * 12);

            ret = m_triangleBuffer[0].normal;
        }

        return ret;
    }

    btVector3 MeshGeometry::getVertexTangent(const GLsizei instanceIdx,
                                             const GLsizei verticeIdx) const
    {
        btVector3 ret(0, 0, 0);

        if (instanceIdx < maxNumberOfInstances() &&
            verticeIdx < numberOfVertices())
        {
            GLsizei idx = (instanceIdx * numberOfVertices());
            idx += (verticeIdx * 1);

            memcpy(m_triangleBuffer, m_VertexData + idx,
                   sizeof(TexturedColoredVertex) * 12);

            ret = m_triangleBuffer[0].tangent;
        }

        return ret;
    }

    btVector3 MeshGeometry::getVertexBitangent(const GLsizei instanceIdx,
                                               const GLsizei verticeIdx) const
    {
        btVector3 ret(0, 0, 0);

        if (instanceIdx < maxNumberOfInstances() &&
            verticeIdx < numberOfVertices())
        {
            GLsizei idx = (instanceIdx * numberOfVertices());
            idx += (verticeIdx * 1);

            memcpy(m_triangleBuffer, m_VertexData + idx,
                   sizeof(TexturedColoredVertex) * 12);

            ret = m_triangleBuffer[0].bitangent;
        }

        return ret;
    }

    void MeshGeometry::setVertexPosition(const btVector3 &v,
                                         const GLsizei instanceIdx,
                                         const GLsizei verticeIdx)
    {
        if (instanceIdx < maxNumberOfInstances() &&
            verticeIdx < numberOfVertices())
        {
            unsigned long offset = instanceIdx * numberOfVertices();
            m_VertexData[offset + verticeIdx].vertex = v;
        }

        //        for (unsigned long vertexIndex = 0;
        //             vertexIndex < numberOfVertices();
        //             vertexIndex++)
        //        {
        //            m_VertexData[offset + verticeIdx].color = c;
        //        }

        //        long index = getGeometryIndex(node);
        //
        //        if(index >= 0 && m_VertexData)
        //        {
        //            bool hidden = node->isHiddenGeometry();
        //
        //            btVector4 c(node->getColorBase());
        //
        //            if(hidden)
        //            c.setW(0.0f);
        //
        //            unsigned long offset = index * numberOfVertices();
        //            for (unsigned long vertexIndex = 0;
        //                 vertexIndex < numberOfVertices();
        //                 vertexIndex++)
        //            {
        //                m_VertexData[offset + vertexIndex].color = c;
        //            }
        //            enableVertexArrayBufferChanged(true);
        //        }
        //
        //
        //
        //        btVector3 ret(0,0,0);
        //
        //        if(instanceIdx < maxNumberOfInstances() &&
        //           verticeIdx < numberOfVertices())
        //        {
        //            GLsizei idx = (instanceIdx * numberOfVertices());
        //            idx += (verticeIdx * 1);
        //
        //            memcpy(m_triangleBuffer,
        //                   m_VertexData + idx,
        //                   sizeof(TexturedColoredVertex) * 12);
        //
        //            ret = m_triangleBuffer[0].vertex;
        //        }
        //
        //        return ret;
    }

    void MeshGeometry::setVertexColor(const btVector4 &v,
                                      const GLsizei instanceIdx,
                                      const GLsizei verticeIdx)
    {
        if (instanceIdx < maxNumberOfInstances() &&
            verticeIdx < numberOfVertices())
        {
            unsigned long offset = instanceIdx * numberOfVertices();
            m_VertexData[offset + verticeIdx].color = v;
        }
    }

    void MeshGeometry::setVertexTexture(const btVector2 &v,
                                        const GLsizei instanceIdx,
                                        const GLsizei verticeIdx)
    {
        if (instanceIdx < maxNumberOfInstances() &&
            verticeIdx < numberOfVertices())
        {
            unsigned long offset = instanceIdx * numberOfVertices();
            m_VertexData[offset + verticeIdx].texture = v;
        }
    }

    void MeshGeometry::setVertexNormal(const btVector3 &v,
                                       const GLsizei instanceIdx,
                                       const GLsizei verticeIdx)
    {
        if (instanceIdx < maxNumberOfInstances() &&
            verticeIdx < numberOfVertices())
        {
            unsigned long offset = instanceIdx * numberOfVertices();
            m_VertexData[offset + verticeIdx].normal = v;
        }
    }

    void MeshGeometry::setVertexTangent(const btVector3 &v,
                                        const GLsizei instanceIdx,
                                        const GLsizei verticeIdx)
    {
        if (instanceIdx < maxNumberOfInstances() &&
            verticeIdx < numberOfVertices())
        {
            unsigned long offset = instanceIdx * numberOfVertices();
            m_VertexData[offset + verticeIdx].tangent = v;
        }
    }

    void MeshGeometry::setVertexBitangent(const btVector3 &v,
                                          const GLsizei instanceIdx,
                                          const GLsizei verticeIdx)
    {
        if (instanceIdx < maxNumberOfInstances() &&
            verticeIdx < numberOfVertices())
        {
            unsigned long offset = instanceIdx * numberOfVertices();
            m_VertexData[offset + verticeIdx].bitangent = v;
        }
    }

    TexturedColoredVertex
    MeshGeometry::getVertex(const GLsizei instanceIdx,
                            const GLsizei verticeIdx) const
    {
        TexturedColoredVertex ret;

        if (instanceIdx < maxNumberOfInstances() &&
            verticeIdx < numberOfVertices())
        {
            GLsizei idx = (instanceIdx * numberOfVertices());
            idx += (verticeIdx * 1);

            memcpy(m_triangleBuffer, m_VertexData + idx,
                   sizeof(TexturedColoredVertex) * 12);

            ret = m_triangleBuffer[0];
        }

        return ret;
    }

    void MeshGeometry::setVertex(const TexturedColoredVertex &tcv,
                                 const GLsizei instanceIdx,
                                 const GLsizei verticeIdx)
    {
        if (instanceIdx < maxNumberOfInstances() &&
            verticeIdx < numberOfVertices())
        {
            unsigned long offset = instanceIdx * numberOfVertices();
            m_VertexData[offset + verticeIdx] = tcv;
        }
    }

    void MeshGeometry::subdivideTriangle(const TexturedColoredVertex &p0,
                                         const TexturedColoredVertex &p1,
                                         const TexturedColoredVertex &p2,
                                         TexturedColoredVertex *triangleBuffer,
                                         GLsizei newIndiceStart,
                                         GLuint *indiceBuffer)
    {
        TexturedColoredVertex p0p1 = TexturedColoredVertex::average(p0, p1);
        TexturedColoredVertex p1p2 = TexturedColoredVertex::average(p1, p2);
        TexturedColoredVertex p2p0 = TexturedColoredVertex::average(p2, p0);

        triangleBuffer[0] = p0;
        triangleBuffer[1] = p0p1;
        triangleBuffer[2] = p2p0;

        triangleBuffer[3] = p0p1;
        triangleBuffer[4] = p1;
        triangleBuffer[5] = p1p2;

        triangleBuffer[6] = p2p0;
        triangleBuffer[7] = p1p2;
        triangleBuffer[8] = p2;

        triangleBuffer[9] = p0p1;
        triangleBuffer[10] = p1p2;
        triangleBuffer[11] = p2p0;

        for (GLsizei i = 0; i < 12; i++)
            indiceBuffer[i] = newIndiceStart + i;
    }

    void MeshGeometry::loadData()
    {
        std::vector<btVector3> vertices;
        std::vector<btVector3> normals;
        std::vector<btVector2> texture;
        std::vector<std::string> faces;

        std::stringstream ss_line(m_Filedata);
        std::string line;

        enum parsemode
        {
            none,
            v,
            vn,
            vt,
            f
        };
        parsemode mode = none;
        btVector3 vec3;
        btVector2 vec2;

        float maxX = 0, maxY = 0, maxZ = 0;

        while (std::getline(ss_line, line, '\n'))
        {
            if (line[0] == '#')
                continue;

            std::replace(line.begin(), line.end(), '\t', ' ');
            std::replace(line.begin(), line.end(), '\r', ' ');

            std::stringstream ss_token(line);
            std::string token;
            int tokencount = 0;
            vec3 = btVector3(0, 0, 0);
            vec2 = btVector2(0, 0);

            while (std::getline(ss_token, token, ' '))
            {
                if (tokencount == 0)
                {
                    if (token == "v")
                        mode = v;
                    else if (token == "vt")
                        mode = vt;
                    else if (token == "vn")
                        mode = vn;
                    else if (token == "f")
                        mode = f;
                    //                    else
                    //                        mode = none;
                }
                else
                {
                    //                    if(!isFloat(token))
                    //                        continue;
                    switch (mode)
                    {
                    case v:
                    case vn:
                    {
                        switch (tokencount)
                        {
                        case 1:
                            vec3.setX(atof(token.c_str()));
                            break;
                        case 2:
                            vec3.setY(atof(token.c_str()));
                            break;
                        case 3:
                            vec3.setZ(atof(token.c_str()));
                            break;
                        default:
                            assert(false);
                        }
                    }
                    break;
                    case vt:
                    {
                        switch (tokencount)
                        {
                        case 1:
                            vec2.setX(atof(token.c_str()));
                            break;
                        case 2:
                            vec2.setY(atof(token.c_str()));
                            break;
                        default:
                            assert(false);
                        }
                    }
                    break;
                    case f:
                    {
                        faces.push_back(token);
                    }
                    break;

                    default:
                        break;
                    }
                }
                tokencount++;
            }

            switch (mode)
            {
            case v:
                maxX = std::max<float>(vec3.x(), maxX);
                maxY = std::max<float>(vec3.y(), maxY);
                maxZ = std::max<float>(vec3.z(), maxZ);

                vertices.push_back(vec3);
                break;
            case vn:
                normals.push_back(vec3);
                break;
            case vt:
                texture.push_back(vec2);
                break;
            case f:
            {
            }
            break;

            default:
                break;
            }
            mode = none;
        }

        m_NumberOfIndices = (GLsizei)faces.size();
        m_NumberOfVertices = (GLsizei)faces.size();
        TexturedColoredVertex *vertexData =
            new TexturedColoredVertex[numberOfVertices()];
        GLuint *indiceData = new GLuint[numberOfIndices()];
        unsigned long idx = 0;

        for (std::vector<std::string>::iterator i = faces.begin();
             i != faces.end(); i++, idx++)
        {
            std::string faceString = *i;
            std::stringstream ss_faceData(*i);
            std::string faceData;
            int ii = 0;
            TexturedColoredVertex t;

            while (std::getline(ss_faceData, faceData, '/'))
            {
                unsigned long idx = atoi(faceData.c_str()) - 1;

                switch (ii)
                {
                case 0:
                    // vertex idx
                    assert(idx < vertices.size());
                    t.vertex = vertices.at(idx);
                    break;
                case 1:
                    assert(idx < texture.size());
                    t.texture = texture.at(idx);
                    // texture idx
                    //                            vertexData[vertexIndex].texture
                    //                            = texture.at(idx);
                    break;
                case 2:
                    assert(idx < normals.size());
                    // normal idx
                    t.normal = normals.at(idx);
                    break;

                default:
                    assert(false);
                    break;
                }
                ii++;
            }

            t.color = btVector4(1.0f, 1.0f, 1.0f, 1.0f);

            vertexData[idx] = t;
            indiceData[idx] = (GLuint)idx;
        }

        Geometry::loadData();

        assert(m_VertexData == NULL);
        m_VertexData = new TexturedColoredVertex[numberOfVertices() *
                                                 maxNumberOfInstances() *
                                                 subdivisionBufferSize()];
        memset(m_VertexData, 0,
               getVertexArrayBufferSize() * subdivisionBufferSize());

        assert(m_VertexDataBuffer == NULL);
        m_VertexDataBuffer = new TexturedColoredVertex[numberOfVertices() *
                                                       maxNumberOfInstances() *
                                                       subdivisionBufferSize()];
        memset(m_VertexDataBuffer, 0,
               getVertexArrayBufferSize() * subdivisionBufferSize());
        enableVertexArrayBufferChanged(true);

        assert(m_IndiceData == NULL);
        m_IndiceData = new GLuint[numberOfIndices() * maxNumberOfInstances() *
                                  subdivisionBufferSize()];
        memset(m_IndiceData, 0,
               getElementArrayBufferSize() * subdivisionBufferSize());

        assert(m_IndiceDataBuffer == NULL);
        m_IndiceDataBuffer =
            new GLuint[numberOfIndices() * maxNumberOfInstances() *
                       subdivisionBufferSize()];
        memset(m_IndiceDataBuffer, 0,
               getElementArrayBufferSize() * subdivisionBufferSize());
        enableIndiceArrayBufferChanged(true);

        unsigned long vertexInstanceIndex = 0;
        unsigned long indiceInstanceIndex = 0;
        for (unsigned long meshIndex = 0; meshIndex < maxNumberOfInstances();
             meshIndex++)
        {
            for (unsigned long verticeIndex = 0;
                 verticeIndex < numberOfVertices(); verticeIndex++)
            {
                m_VertexData[vertexInstanceIndex] = vertexData[verticeIndex];
                vertexInstanceIndex++;
            }

            for (unsigned long indiceIndex = 0; indiceIndex < numberOfIndices();
                 indiceIndex++)
            {
                m_IndiceData[indiceInstanceIndex] = (GLuint)(
                    (meshIndex * numberOfVertices()) + indiceData[indiceIndex]);
                indiceInstanceIndex++;
            }
        }

        TexturedColoredVertex::computeTangentBasis(m_VertexData,
                                                   numberOfVertices());

        delete[] indiceData;
        indiceData = NULL;

        delete[] vertexData;
        vertexData = NULL;
    }

    void MeshGeometry::unLoadData()
    {
        Geometry::unLoadData();

        if (m_IndiceData)
            delete[] m_IndiceData;
        m_IndiceData = NULL;

        if (m_VertexData)
            delete[] m_VertexData;
        m_VertexData = NULL;
    }

    const void *MeshGeometry::getVertexArrayBufferPtr() const
    {
        return (const void *)m_VertexData;
    }

    GLsizeiptr MeshGeometry::getVertexArrayBufferSize() const
    {
        GLsizeiptr size = sizeof(TexturedColoredVertex) * numberOfVertices() *
                          maxNumberOfInstances();
        return size;
    }

    const void *MeshGeometry::getElementArrayBufferPtr() const
    {
        return m_IndiceData;
    }

    GLsizeiptr MeshGeometry::getElementArrayBufferSize() const
    {
        GLsizeiptr size =
            sizeof(GLuint) * numberOfIndices() * maxNumberOfInstances();
        return size;
    }

    GLenum MeshGeometry::getElementIndexType() const { return GL_UNSIGNED_INT; }

    void MeshGeometry::setOpacity(Node *node)
    {
        long index = getGeometryIndex(node);

        if (index >= 0 && m_VertexData)
        {
            float opacity = node->getOpacity();
            bool hidden = node->isHiddenGeometry();

            float o =
                (opacity > 1.0f) ? 1.0f : ((opacity < 0.0f) ? 0.0f : opacity);
            o = (hidden) ? 0.0f : o;

            unsigned long offset = index * numberOfVertices();
            for (unsigned long vertexIndex = 0;
                 vertexIndex < numberOfVertices(); vertexIndex++)
            {
                btVector4 color(m_VertexData[vertexIndex + offset].color);
                color.setW(o);

                m_VertexData[vertexIndex + offset].color = color;
            }
            enableVertexArrayBufferChanged(true);
        }
    }

    void MeshGeometry::setHidden(Node *node, bool hiddenFromCamera)
    {
        long index = getGeometryIndex(node);

        if (index >= 0 && m_VertexData)
        {
            bool hidden = node->isHiddenGeometry() || hiddenFromCamera;

            float alpha = (hidden) ? 0.0f : 1.0f;

            unsigned long offset = index * numberOfVertices();
            for (unsigned long vertexIndex = 0;
                 vertexIndex < numberOfVertices(); vertexIndex++)
            {
                btVector4 color(m_VertexData[vertexIndex + offset].color);
                color.setW(alpha);

                m_VertexData[vertexIndex + offset].color = color;
            }
            enableVertexArrayBufferChanged(true);
        }
    }

    void MeshGeometry::setColorBase(Node *node)
    {
        long index = getGeometryIndex(node);

        if (index >= 0 && m_VertexData)
        {
            bool hidden = node->isHiddenGeometry();

            btVector4 c(node->getColorBase());

            if (hidden)
                c.setW(0.0f);

            unsigned long offset = index * numberOfVertices();
            for (unsigned long vertexIndex = 0;
                 vertexIndex < numberOfVertices(); vertexIndex++)
            {
                m_VertexData[offset + vertexIndex].color = c;
            }
            enableVertexArrayBufferChanged(true);
        }
    }

    void MeshGeometry::applyShape(Node *node, PhysicsShape *physicsShape)
    {
        assert(false && "must implment");
        //        btVector2 halfExtends(getDimensions(node) * 0.5f);
        //
        //        //        if(NULL != (shape2d  =
        //        //        dynamic_cast<PhysicsShapeBox2D*>(physicsShape)))
        //        if (strcmp(physicsShape->getClassName(), "PhysicsShapeBox2D")
        //        == 0)
        //        {
        //            PhysicsShapeBox2D *shape2d =
        //            reinterpret_cast<PhysicsShapeBox2D *>(physicsShape);
        //            shape2d->setHalfExtends(halfExtends);
        //        }
        //        //        else if(NULL != (shape3d  =
        //        //        dynamic_cast<PhysicsShapeBox*>(physicsShape)))
        //        else if (strcmp(physicsShape->getClassName(),
        //        "PhysicsShapeBox")
        //        == 0)
        //        {
        //            PhysicsShapeBox *shape3d =
        //            reinterpret_cast<PhysicsShapeBox *>(physicsShape);
        //            btVector3 halfExtends3d(halfExtends.x(),
        //            halfExtends.y(), 1.0f);
        //            shape3d->setHalfExtends(halfExtends3d);
        //        }
        //
        //        s64 spriteIndex = node->getGeometryIndex();
        //        m_changedDimensionArray[spriteIndex] = false;
    }

    bool MeshGeometry::shouldApplyShape(Node *node) const
    {
        assert(false && "must implemnt");
        //        s64 spriteIndex = node->getGeometryIndex();
        //        if (spriteIndex >= 0)
        //        {
        //            return m_changedDimensionArray[spriteIndex];
        //        }
        return false;
    }

    void MeshGeometry::transformVertices(Node *node,
                                         const btTransform &transfrom)
    {
        assert(false && "todo");
    }

    void MeshGeometry::transformVertexColors(Node *node,
                                             const btTransform &transform)
    {

        assert(false && "todo");
    }

    void MeshGeometry::transformTextureCoordinates(Node *node,
                                                   const btTransform &transform)
    {

        assert(false && "todo");
    }

    GLsizei MeshGeometry::numberOfVertices() const
    {
        return m_NumberOfVertices;
    }

    GLsizei MeshGeometry::numberOfIndices() const { return m_NumberOfIndices; }

} // namespace njli
