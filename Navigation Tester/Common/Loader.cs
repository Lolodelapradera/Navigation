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
        private delegate void AddBlackListDelegate(uint Mapid, string name, XYZ p, float radius, uint Type);
        private static AddBlackListDelegate Blacklist;


        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void NativationDebugger(bool OnOROff);
        private static NativationDebugger debugger;

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

            var _Debugger = GetProcAddress(navProcPtr, "Debugger");
            if (freePathPtr != IntPtr.Zero)
            {

                debugger = Marshal.GetDelegateForFunctionPointer<NativationDebugger>(_Debugger);
            }
        }

        public static void AddBlackList(uint Mapid, string Name, Vector3 p, float radius, uint Type)
        {
            try
            {
                Blacklist(Mapid, Name, p.ToXYZ(), radius, Type);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error AddBlackList: {ex.Message}");
            }
        }

        internal static void NavigationDebugger(bool OnOrOff)
        {
            debugger(OnOrOff);
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
