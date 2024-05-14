using System;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;

namespace Navigation_Tester.Common
{
    internal unsafe class Loader
    {
        [DllImport("kernel32.dll")]
        static extern IntPtr LoadLibrary(string lpFileName);

        [DllImport("kernel32.dll")]
        static extern IntPtr GetProcAddress(IntPtr hModule, string procName);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate XYZ* CalculatePathDelegate(
           uint mapId,
           XYZ start,
           XYZ end,
           out int length);

        private static CalculatePathDelegate calculatePath;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void FreePathArr(XYZ* pathArr);

        //private static CalculatePathDelegate calculatePath;
        private static FreePathArr freePathArr;

        internal static void Load()
        {
            var currentFolder = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);

            var mapsPath = $"{currentFolder}\\Navigation.dll";

            var navProcPtr = LoadLibrary(mapsPath);
            

            var calculatePathPtr = GetProcAddress(navProcPtr, "CalculatePath");
            if (calculatePathPtr != IntPtr.Zero)
            {

                calculatePath = Marshal.GetDelegateForFunctionPointer<CalculatePathDelegate>(calculatePathPtr);

            }
            var freePathPtr = GetProcAddress(navProcPtr, "FreePathArr");
            if (freePathPtr != IntPtr.Zero)
            {

                freePathArr = Marshal.GetDelegateForFunctionPointer<FreePathArr>(freePathPtr);
            }
        }

        internal static Vector3[] CalculatePath(uint mapId, Vector3 start, Vector3 end)
        {
            try
            {

                var ret = calculatePath(mapId, start.ToXYZ(), end.ToXYZ(), out int length);
                var list = new Vector3[length];
                for (var i = 0; i < length; i++)
                {
                    list[i] = new Vector3(ret[i]);
                }

                freePathArr(ret);
                return list;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error CalculatePath: {ex.Message}");
                return new Vector3[0];
            }
        }
    }
}
