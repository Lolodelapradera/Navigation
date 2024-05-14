using System;
using System.Runtime.InteropServices;

namespace Navigation_Tester.Common
{
    [StructLayout(LayoutKind.Sequential)]
    public class Vector3
    {
        public float X { get; set; }
        public float Y { get; set; }
        public float Z { get; set; }
        public Vector3() { }

        public Vector3(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public Vector3(XYZ xyz)
        {
            X = xyz.X;
            Y = xyz.Y;
            Z = xyz.Z;
        }

        public XYZ ToXYZ() => new XYZ(X, Y, Z);

        public bool IsVaild
        {
            get
            {
                return this.X != 0 || this.Y != 0 || this.Z != 0;
            }
        }


        public static Vector3 operator +(Vector3 v1, Vector3 v2)
        {
            return new Vector3(v1.X + v2.X, v1.Y + v2.Y, v1.Z + v2.Z);
        }

        // Subtraction
        public static Vector3 operator -(Vector3 v1, Vector3 v2)
        {
            return new Vector3(v1.X - v2.X, v1.Y - v2.Y, v1.Z - v2.Z);
        }

        // Scalar multiplication
        public static Vector3 operator *(Vector3 v, float scalar)
        {
            return new Vector3(v.X * scalar, v.Y * scalar, v.Z * scalar);
        }

        // Scalar multiplication (reverse order)
        public static Vector3 operator *(float scalar, Vector3 v)
        {
            return v * scalar; // Reuse the other operator overload
        }

        // String representation of the vector
        public override string ToString()
        {
            return $"new Vector3({X}, {Y}, {Z}),";
        }

        // Addition, subtraction, scalar multiplication operators...

        // Method to calculate 2D distance between two vectors
        public float Distance2D(Vector3 other)
        {
            float deltaX = X - other.X;
            float deltaY = Y - other.Y;
            return (float)Math.Sqrt(deltaX * deltaX + deltaY * deltaY);
        }

        // Method to calculate 3D distance between two vectors
        public float Distance3D(Vector3 other)
        {
            float deltaX = X - other.X;
            float deltaY = Y - other.Y;
            float deltaZ = Z - other.Z;
            return (float)Math.Sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
        }


        public float DistanceTo(Vector3 position)
        {
            if (position.Z == 0 || Z == 0)
                return (float)System.Math.Sqrt((Math.Pow((X - position.X), 2.0) + Math.Pow((Y - position.Y), 2.0)));

            return (float)System.Math.Sqrt((Math.Pow((X - position.X), 2.0) + Math.Pow((Y - position.Y), 2.0)) +
                          System.Math.Pow((Z - position.Z), 2.0));
        }
    }
}
