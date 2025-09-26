package SuiDesigner

#include <stdio.h>


import * from "../Sui/Dialog/MessageDialog.orc"
import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Path.orc"
import * from "./EventFileItemChanged.orc"



class FileItem {
    String@ filename = str("");
    List@ children = new List()
    String@ path = str("")
    FileItem @parent = null

    bool isDirectory = false

    // -1: unknown, 0: no, 1: yes
    // int _hasSubDirectory = 0

    //子目录构成的列表
    List@ subDirectoryChildren = null

    List@ getSubDirectoryChildren(){
        if (!self.isDirectory){
            return null
        }

        if (self.subDirectoryChildren == null){
            List@ ret = new List()
            int l = self.children.size()
            for (int i = 0; i < l; i++){
                FileItem *kid = (FileItem*)self.children.get(i)
                if (kid && kid.isDirectory){
                    ret.add(kid)
                }
            }
            return ret
        }
        return null
    }

    //是否有子目录
    bool hasSubDirectory(){
        List@ tmp = self.getSubDirectoryChildren()
        return tmp != null && tmp.size() > 0
        // if (self.isDirectory){
        //     if (self._hasSubDirectory == -1){
        //         self._hasSubDirectory = 0
        //         for (int i = 0, l = self.children.size(); i < l; i++){
        //             FileItem *kid = (FileItem*)self.children.get(i)
        //             if (kid && kid.isDirectory){
        //                 self._hasSubDirectory = 1
        //                 break
        //             }
        //         }
        //     }
        // }
        // return self._hasSubDirectory == 1
    }

    void appendChild(FileItem@ fi){
        fi.removeSelf()
        self.children.add(fi)
        fi.parent = self
    }
    void removeChild(FileItem *fi){
        if (fi.parent == self){
            self.children.remove(fi)
            fi.parent = null
        }
    }
    void removeSelf(){
        if (self.parent){
            self.parent.removeChild(self)
        }
    }

    void setPathByParentPathAndFilename(String@ parentPath, String@ filename){
        String@ path = parentPath.clone().add("/").addString(filename)
        self.setPath(path)
    }
    void setPath(String@ path){
        self.path = path
        self.filename = Path_basename(path.str)
        self.isDirectory = Path_isDirectory(self.path.str)
    }

    //通过父路径和自己的filename来更新路径
    void updatePathByParentPathAndSelfFilename(){
        if self.parent {
            self.path = str(self.parent.path.str).add("/").addString(self.filename)
        }
    }
    //更新整棵子树 path
    void updatePathByParnetPathAndSelfFilename_subtree(){
        self.updatePathByParentPathAndSelfFilename()
        for (int i = 0; i < self.children.size(); i++){
            FileItem *fi = (FileItem*)self.children.get(i)
            fi.updatePathByParnetPathAndSelfFilename_subtree()
        }
    }

    void loadSubtree(){
        if (self.isDirectory){
            self.children.clear()

            List@ paths = Path_list(self.path.str)
            int l = paths.size()
            for (int i = 0; i < l; i++){
                String@ kidPath = (String@)paths.get(i)

                FileItem @kid = new FileItem()
                kid.setPath(kidPath)

                self.appendChild(kid)

                if (kid.isDirectory){
                    kid.loadSubtree()
                }
            }
        }
    }

    void printTree(int tab){
        for (int i = 0; i < tab; i++){
            printf("\t");
        }
        printf("%s :%s dir:%d kids:%d\n", self.path.str, self.filename.str, self.isDirectory, self.children.size())
        for (int i = 0; i < self.children.size(); i++){
            FileItem *fi = (FileItem*)self.children.get(i)
            fi.printTree(tab + 1)
        }
    }

}

FileItem@ FileItem_loadDirectoryTree(const char *dir){
    FileItem@ root = new FileItem()
    root.setPath(str(dir))
    root.loadSubtree()

    return root
}