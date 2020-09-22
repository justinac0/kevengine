import bpy
import os

vertices = []
indices  = []
normals  = []

scene_objects = bpy.data.objects

# read data into lists

output = open('file.znk','w')

for obj in scene_objects:
    # can only export meshes at this stage
    if obj.type == 'MESH':
        for v in obj.data.vertices:
            vertices.append(v.co[0])
            vertices.append(v.co[1])
            vertices.append(v.co[2])
        for polygon in obj.data.polygons:
            verts_in_face = polygon.vertices[:]
            normals.append(polygon.normal[0])
            normals.append(polygon.normal[1])
            normals.append(polygon.normal[2])
            for vert in verts_in_face:
                indices.append(vert);
                vertices.append(obj.data.vertices[vert].co[0])

        output.write('; vertices')
        # vertices
        for i in range(len(vertices)):
            if (i % 3) == 0:
                output.write('\n')
            output.write(str(vertices[i]) + ' ')
        # normals
        output.write('\n\n; normals')
        for i in range(len(normals)):
            if (i % 3) == 0:
                output.write('\n')
            output.write(str(normals[i]) + ' ')
        # indices
        output.write('\n\n; indices')
        for i in range(len(indices)):
            if (i % 3) == 0:
                output.write('\n')
            output.write(str(indices[i]) + ' ')

        output.write('\n\n; model ' + obj.name + '\n\n') # should be exporting for each shape in scene

output.close()