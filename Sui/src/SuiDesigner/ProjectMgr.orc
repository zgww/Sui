package SuiDesigner

#include <stdio.h>

import * from "../Orc/String.orc"
import * from "../Orc/Path.orc"
import * from "../Orc/List.orc"
import * from "../Orc/List.orc"
import * from "../Json/Json.orc"


class ProjectInfo {
    String@ path = str(".")
    String@ version = str("1.0.0")
    String@ icon = str("./asset/icon/dir.png")

    Json@ toJson(){
        Json@ jo = Json_mkObject()
        jo.putString("path", self.path)
        jo.putString("version", self.version)
        return jo
    }
    void fromJson(Json@ jo){
        self.path = jo.getString("path")
        self.version = jo.getString("path")
    }
    String@ getName(){
        return Path_basename(self.path.str)
    }
}
class ProjectMgr {
    List@ projects = new List()

    void ctor(){
        self.addTestProject("E:/luwa/oms_ts/Sui/asset/icon")
        self.addTestProject("E:/luwa/oms_ts/Sui/asset")
        self.addTestProject("E:/luwa/oms_ts/Sui")
        self.addTestProject("E:/luwa/oms_ts")
        self.addTestProject("E:/luwa/oms_ts/orc-antlr")
    }
    void addTestProject(const char *path){
        ProjectInfo@ p = new ProjectInfo()
        p.path = str(path)
        p.version = str("2.303.0")
        self.projects.add(p)
    }

    Json@ toJson(){
        Json@ projectsJa = Json_mkArray()

        for int i = 0; i < self.projects.size(); i++{
            ProjectInfo@ project = (ProjectInfo@)self.projects.get(i)
            Json@ projectJo = project.toJson()
            projectsJa.add(projectJo)
        }

        Json@ jo = Json_mkObject()
        jo.put("projects", projectsJa)

        return jo
    }

    void loadByJson(Json@ jo){
        self.projects = new List()
        Json@ projectsJa = jo.get("projects")
        for int i = 0; i < projectsJa.arraySize(); i++{
            Json@ projectJo = projectsJa.at(i)
            ProjectInfo@ project = new ProjectInfo()
            project.fromJson(projectJo)
            self.projects.add(project)
        }
    }



    void importProject(String@ projectRootDirPath){
    }
    void remove(ProjectInfo* project){
        self.projects.remove(project)
        self.save()
    }
    void add(ProjectInfo@ project){
        self.projects.add(project)
        self.save()
    }

    void save(){
        Json@ jo = self.toJson()
        String@ text = jo.dump()
        printf("save ProjectMgr. %s\n", text.str)
    }
    void load(){
    }
}

// ProjectMgr@ ProjectMgr_ins(){
//     static ProjectMgr@ mgr = null
//     if !mgr {
//         mgr = new ProjectMgr()
//     }
//     return mgr
// }
