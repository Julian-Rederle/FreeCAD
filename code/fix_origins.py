import FreeCAD as App

# TODO: Implement

# Get the current document
doc = App.ActiveDocument


# Reference the Body object
top = doc.Body007

# Create axes and planes if they do not already exist
x_axis = doc.addObject('PartDesign::CoordinateSystem', 'X_Axis007')
y_axis = doc.addObject('PartDesign::CoordinateSystem', 'Y_Axis007')
z_axis = doc.addObject('PartDesign::CoordinateSystem', 'Z_Axis007')
xy_plane = doc.addObject('PartDesign::Plane', 'XY_Plane007')
xz_plane = doc.addObject('PartDesign::Plane', 'XZ_Plane007')
yz_plane = doc.addObject('PartDesign::Plane', 'YZ_Plane007')

# Add these features to the body so they are properly grouped
top.addObject(x_axis)
top.addObject(y_axis)
top.addObject(z_axis)
top.addObject(xy_plane)
top.addObject(xz_plane)
top.addObject(yz_plane)

# Assign the features to the OriginFeatures property of the Origin
origin = top.Origin
origin.OriginFeatures = [x_axis, y_axis, z_axis, xy_plane, xz_plane, yz_plane]

# Recompute the document to apply the changes
doc.recompute()

print("Axes and planes created and assigned to the Origin of Body007.")