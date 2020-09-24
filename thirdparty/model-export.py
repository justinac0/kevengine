import bpy
import random
import math
import os

class Vector3:
    def __init__(self, x=0, y=0, z=0):
        self.x = x
        self.y = y
        self.z = z

    def __str__(self):
        return "{0} {1} {2}\n".format(self.x, self.y, self.z)

    def __add__(self, v2):
        return Vector3(self.x + v2.x, self.y + v2.y, self.z + v2.z)

    def __sub__(self, v2):
        return Vector3(self.x - v2.x, self.y - v2.y, self.z - v2.z)

    def __mul__(self, v2):
        return Vector3(self.x * v2.x, self.y * v2.y, self.z * v2.z)

    def __truediv__(self, v2):
        return Vector3(self.x * v2.x, self.y * v2.y, self.z * v2.z)

    def scalar_div(self, value):
        if (value != 0):
            return Vector3(self.x / value, self.y / value, self.z / value)
        else:
            return self

    def scalar_mul(self, value):
        return Vector3(self.x * value, self.y * value, self.z * value)

    def length(self):
        return math.sqrt(self.squared_length())
    
    def squared_length(self):
        return self.x * self.x + self.y * self.y + self.z * self.z

    def dot(self, v2: "Vector3"):
        return self.x * v2.x + self.y * v2.y + self.z * v2.z

    def cross(self, v2: "Vector3"):
        return Vector3( self.y * v2.z - self.z * v2.y,
                        self.z * v2.x - self.x * v2.z,
                        self.x * v2.y - self.y * v2.x )

    def normalize(self):
        return self.scalar_div(self.length())

def CalculateNormals(normals, vertices, indices):
    newNormals = []
    for v in vertices:
        newNormals.append(Vector3(0,0,0))

    for i in range(0, len(indices), 3):
        i0 = indices[i + 0]
        i1 = indices[i + 1]
        i2 = indices[i + 2]

        v1 = vertices[i1] - vertices[i0];
        v2 = vertices[i2] - vertices[i0];

        normal = v1.cross(v2).normalize()

        newNormals[i0] += normal
        newNormals[i1] += normal
        newNormals[i2] += normal

    for i in range(len(vertices)):
        normals.append(newNormals[i].normalize())

def ParseScene():
    scene_objects = bpy.data.objects

    output = open('file.znk','w')

    for obj in scene_objects:
        # can only export meshes at this stage
        if obj.type == 'MESH':
            vertices = []
            indices  = []
            normals  = []
            colours  = []

            for v in obj.data.vertices:
                vertices.append(Vector3(v.co[0], v.co[2], -v.co[1]))

            for i in range(len(vertices)):
                colours.append(Vector3(random.uniform(0.0, 1.0), random.uniform(0.0, 1.0), random.uniform(0.0, 1.0)))

            for polygon in obj.data.polygons:
                verts_in_face = polygon.vertices[:]
                # normals.append(Vector3(polygon.normal[0], polygon.normal[1], polygon.normal[2]))
                for vert in verts_in_face:
                    indices.append(vert)

            output.write('; vertices\n')
            # vertices
            for v in vertices:
                output.write(str(v))

            CalculateNormals(normals, vertices, indices)

            # normals
            output.write('\n; normals\n')
            for n in normals:
                output.write(str(n))

            # colours
            output.write('\n\n; colours\n')
            for c in colours:
                output.write(str(c))

            # indices
            output.write('\n; indices')
            for i in range(len(indices)):
                if (i % 3) == 0:
                    output.write('\n')
                output.write(str(indices[i]) + ' ')

            model_matrix = obj.matrix_world;

            model_position = Vector3(model_matrix[0][3], model_matrix[1][3], model_matrix[2][3])
            model_scale = Vector3(obj.scale[0], obj.scale[1], obj.scale[2])
            model_rotation = Vector3(obj.rotation_euler[0], obj.rotation_euler[1], obj.rotation_euler[2])

            print(model_matrix)

            output.write('\n\n; position\n' + str(model_position))
            output.write('\n; scale\n' + str(model_scale))
            output.write('\n; rotation\n' + str(model_rotation))

            output.write('\n; model ' + obj.name + '\n') # should be exporting for each shape in scene

    output.close()

ParseScene()
