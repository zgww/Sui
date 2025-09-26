
package Sgl

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"

import * from "./Buffer.orc"
import * from "./Vbo.orc"
import * from "./Material.orc"
import * from "./Program.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Math.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Orc/String.orc"

import * from "./Geometry.orc"
import * from "./GeometryCylinder.orc"


class GeometryCone extends GeometryCylinder {

    void ctor(){
        self.radiusTop = 0
    }
}
