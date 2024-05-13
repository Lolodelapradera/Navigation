# Navigation

## About


In the realm of World of Warcraft, our navigation project is built upon the formidable foundations of Recast and Detour. As adventurers traverse the vast landscapes of Azeroth, our mission is to ensure seamless pathfinding through the intricate terrains and sprawling landscapes that define this legendary world.

Within our project, the quest for optimal navigation is paramount. By harnessing the power of Recast and Detour, we forge a path where adventurers can navigate with precision and efficiency. Through meticulous management of navigation meshes and queries, we empower heroes to explore every corner of Azeroth, from the peaks of Mount Hyjal to the depths of the Sunken City of Vashj'ir.

With each map and instance meticulously crafted, our navigation system stands as a testament to our dedication to the World of Warcraft community. As heroes embark on their epic journeys, they can rely on our navigation project to guide them through perilous dungeons, winding forests, and treacherous terrain, ensuring their quests are as immersive and seamless as the world itself.

In this world of magic and mystery, our navigation project serves as a steadfast ally, guiding adventurers on their noble quests and ensuring that the spirit of exploration burns brightly in the hearts of all who venture forth into the realms of Azeroth.


Certainly! Here's a refined version of the instructions presented as a single, cohesive post:

---

## Visual Studio Configuration

To ensure seamless integration of the necessary libraries into your Visual Studio project, follow these straightforward steps:

1. **Open your Visual Studio solution**.

2. **Navigate to the project properties**.

3. **Configure Additional Include Directories**:
   - In the project properties, locate the "VC++ Directories" or "Include Directories" section.
   - Add the following paths to include the required directories:
     ```
     ..\Navigation\Detour\Include
     ..\Navigation\Detour\Include\g3dlite
     ..\Navigation\Utilities
     ```
   These directories contain essential headers and utilities necessary for your project's compilation.

4. **Save your changes** to ensure that the configurations are applied.

By incorporating these directories into your project's additional include directories, Visual Studio will seamlessly locate and include the essential headers from the Detour library and G3D Lite library during compilation.

## Download MMaps

Enhance your navigation capabilities by downloading the MMaps files from the provided link:

[Download MMaps](https://www.mediafire.com/file/qtjykpu383dgbsn/mmaps.7z/file)

---

This unified post provides clear instructions for configuring Visual Studio to include the necessary directories and also offers a convenient link for downloading the MMaps files.

