using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Navigation_Tester.Common
{
    [StructLayout(LayoutKind.Sequential)]
    public struct XYZ
    {
        internal float X;
        internal float Y;
        internal float Z;

        internal XYZ(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }
    }
}
