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

        private static FreePathArr freePathArr;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void AddBlackListDelegate(uint mapId, XYZ p, float radius);
        private static AddBlackListDelegate Blacklist;

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

            var Blacklistptr = GetProcAddress(navProcPtr, "Blacklist");
            if (freePathPtr != IntPtr.Zero)
            {

                Blacklist = Marshal.GetDelegateForFunctionPointer<AddBlackListDelegate>(Blacklistptr);
            }
        }

        internal static void AddToBlacklist(uint mapId, Vector3 p, float radius)
        {
            Blacklist(mapId, p.ToXYZ(), radius);
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
