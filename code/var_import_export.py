import sys
sys.path.append('/usr/lib/freecad/lib')

# Import FreeCAD modules
import FreeCAD as App
import FreeCADGui

# Access the active FreeCAD document
doc = App.ActiveDocument

if doc is None:
    print("No active document found!")
else:
    print(f"Active document: {doc.Name}")