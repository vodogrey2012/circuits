//
// Created by Yauheni Sharamed on 20.11.2021.
//

#ifndef CIRCUITS_CIRCUITACTIVE_H
#define CIRCUITS_CIRCUITACTIVE_H

#include "Circuit.h"
#include "Matrix.h"
#include <deque>
#include <fstream>
#include <string>
#include <regex>
#include <iomanip>
#include <complex>
#include <math.h>

template<typename T>
struct identity { typedef T type; };

template <typename T>
class CircuitActive : public Circuit<T>{
public:
    CircuitActive()= default;
    ~CircuitActive()= default;

    int FindCurrent() {
        if(this->ConnectWires()) return -1;
        FindMaxTree();
        if(wremoved_.size() != 0){
            if(FindMeshCurrents()) return -1;
            FindCurrentsFromMesh();
        }

        PrintResult();

        return 0;
    }

private:
    void PrintResult (){
        return PrintResult (identity<T>());
    }

    void PrintResult (identity<double>){
        for(auto & wire : this->wires_){
            std::cout << wire.GetIndex1() << " -- " << wire.GetIndex2() << ": "
                      << std::setprecision(5) << wire.GetI() << " A" << std::endl;
        }
    }

    void PrintResult (identity<std::complex<double>>){
        for(auto & wire : this->wires_){
            std::cout << wire.GetIndex1() << " -- " << wire.GetIndex2() << ": "
                      << std::setprecision(5) << std::abs(wire.GetI()) << " A, " << std::arg(wire.GetI()) << std::endl;
        }
    }

    void FindMaxTree() {
        int i = 0;
        for(auto & wire : this->wires_){
#ifdef DEBUG
            std::cout << i << std::endl;
#endif
            i++;
            Point<T> start;
            for(auto & point : this->points_){
                auto allel = point.GetAllElements();
                auto it = std::find_if(allel.begin(), allel.end(), [&wire](const typename Point<T>::pPElement& element){ return element.second->GetWindex() == wire.GetWindex();});
                if(it != allel.end())
                    start = *it->first;
            }
            auto full = FindAllVisitedPoints(start);

            wire.SetExcluded(true);
            if(IsMonoTree(start, full))
                wremoved_.emplace_back(&wire);
            else
                wire.SetExcluded(false);
        }
    }

    bool IsMonoTree(Point<T> start, std::vector<int> full) {
        std::vector<int> pvisited = FindAllVisitedPoints(start);

        for(const auto& point1 : full) {
            if(std::find(pvisited.begin(), pvisited.end(), point1) == pvisited.end())
                return false;
        }
        return true;
    }

    std::vector<int> FindAllVisitedPoints(Point<T> start) {
        std::vector<int> wvisited;
        std::vector<int> pvisited;
        std::deque<Point<T>> deq;
        auto point = start;
        pvisited.push_back(point.GetIndex());
        deq.push_back(point);
        deq.push_back(point);
        do{
            bool is_next_point = false;
            for(auto elem : point.GetAllElements()){
                if(     std::find(wvisited.begin(), wvisited.end(), elem.second->GetWindex()) == wvisited.end()
                        && !elem.second->IsExcluded()){
                    point = *elem.first;
                    deq.push_back(point);
                    pvisited.push_back(point.GetIndex());
                    wvisited.push_back(elem.second->GetWindex());
                    is_next_point = true;
                    break;
                }
            }
            if (!is_next_point){
                deq.pop_back();
                if(!deq.empty())
                    point = deq.back();
            }

        } while(!deq.empty());

        return pvisited;
    }

    void CalcMatrix(Matrix<T> & C, Matrix<T> & Z, Matrix<T> & E) {
        for(size_t i = 0; i < E.GetIDem(); ++i){
            Z[i][i] = this->wires_[i].GetR();
        }

        for(size_t i = 0; i < C.GetIDem(); ++i){
            wremoved_[i]->SetExcluded(false);
            auto path = FindNoMonoTreePath(*wremoved_[i]);

#ifdef DEBUG
            for(auto & r : path)
            std::cout << r ;
        std::cout << std::endl;
#endif
            no_mono_paths_.emplace_back(std::make_pair(path, 0));
            for(size_t j = 0; j < C.GetJDem(); ++j){
                for(size_t k = 0; k < path.size(); ++k){
                    if(path[k] == this->wires_[j].GetWindex()) {
                        C[i][j] = 1;
                        E[j][0] = this->wires_[j].GetE();
                    }
                    else if(path[k] == -1 * this->wires_[j].GetWindex()){
                        C[i][j] = -1;
                        E[j][0] = this->wires_[j].GetE();
                    }
                }
            }
            wremoved_[i]->SetExcluded(true);
        }

    }

    int FindMeshCurrents() {
        std::unique_ptr<Matrix<T>> left;
        std::unique_ptr<Matrix<T>> right;
        try{
            Matrix<T>    C(wremoved_.size(), this->wires_.size());
            Matrix<T> Z(this->wires_.size(), this->wires_.size());
            Matrix<T> E(this->wires_.size(), 1);
            CalcMatrix(C, Z, E);
            left = std::make_unique<Matrix<T>>();
            right = std::make_unique<Matrix<T>>();
            *left = (C*Z*C.Transponse());
            *right = C*E;
#ifdef DEBUG
    std::cout << "MATRIX C =\n" << C << std::endl;
    std::cout << "MATRIX Z =\n"<< Z << std::endl;
    std::cout << "MATRIX E =\n"<< E << std::endl;
    std::cout << "MATRIX left =\n" << *left << std::endl;
#endif

        }
        catch (const std::exception& err){
            return -1;
        }

        std::vector<T> vright;
        assert(right->GetJDem() == 1);
        vright.reserve(right->GetIDem());
        for(auto i = 0; i < right->GetIDem(); i++)
            vright.emplace_back((*right)[i][0]);

        std::vector<T> res = left->    Gauss(vright.begin(), vright.end());
        if(res.size() == 0){
            std::cerr << "Invalid circuit parameters!" << std::endl;
            return -1;
        }
        for(size_t i = 0; i < res.size(); ++i)
            no_mono_paths_[i].second = res[i];

        left.reset();
        right.reset();
#ifdef DEBUG
        for(auto & it : res)
        std::cout << it << "\t|\n";
#endif
        return 0;
    }

    void FindCurrentsFromMesh() {
        for(auto & wire : this->wires_){
            T i = 0;
            for(auto & path : no_mono_paths_){
                for(size_t k = 0; k < path.first.size(); ++k){
                    if(path.first[k] == wire.GetWindex())
                        i += path.second;
                    else if (path.first[k] == -1*wire.GetWindex())
                        i -= path.second;
                }
            }
            wire.SetI(i);
        }
    }

    std::vector<int> FindNoMonoTreePath(Wire<T> start) {
        std::vector<int> wvisited;
        std::deque<Point<T>> deq;
        std::vector<int> ret;
        auto it = find_if(this->points_.begin(), this->points_.end(), [&start] (const Point<T>& element) { return element.GetIndex() == start.GetIndex1(); } );
        auto point = *it;
        deq.push_back(point);
        do{
            bool is_next_point = false;
            for(auto elem : point.GetAllElements()){
                if(    std::find(wvisited.begin(), wvisited.end(), elem.second->GetWindex()) == wvisited.end()
                       && !elem.second->IsExcluded()){
                    point = *elem.first;
                    deq.push_back(point);
                    if(point.GetIndex() == elem.second->GetIndex1())
                        ret.emplace_back(-1*elem.second->GetWindex());
                    else
                        ret.emplace_back(elem.second->GetWindex());
                    wvisited.push_back(elem.second->GetWindex());
                    is_next_point = true;
                    break;
                }
            }
            if (!is_next_point){
                deq.pop_back();
                ret.pop_back();
                if(deq.size() == 0)
                    break;
                point = deq.back();
            }
        } while(deq.size() == 1 || (deq.front().GetIndex() != deq.back().GetIndex()));

        return ret;
    }

    std::vector<Wire<T>*> wremoved_;
    std::vector<std::pair<std::vector<int>, T>> no_mono_paths_;

private:
    int ReadFromFile (const std::istream& sfile, identity<double>){
        std::stringstream ss;
        ss << sfile.rdbuf();
        std::string s = ss.str();
        s.push_back('\n');

        std::string point1("(\\d+)");
        std::string point2("(\\d+)");
        std::string resist("(-?\\d+(?:\\.\\d+)?)");
        std::string opteds("(?:(-?\\d+(?:\\.\\d+)?)\\s*V?\\s*[;\\n])?");

        std::regex word_regex(point1 + "\\s*--\\s*" + point2 + "\\s*,\\s*" + resist + "\\s*[;\\n]\\s*" + opteds);
        auto words_begin =
                std::sregex_iterator(s.begin(), s.end(), word_regex);
        auto words_end = std::sregex_iterator();

        if(words_begin == words_end){
            std::cerr << "Incorrect input file format." << std::endl;
            return -1;
        }

        int windex = 1;
        for(std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;

            int index1;
            int index2;
            double r;
            double e = 0;
            std::istringstream (match[1]) >> index1;
            std::istringstream (match[2]) >> index2;
            std::istringstream (match[3]) >> r;

            if(match[4].str().length() != 0)
                std::istringstream (match[4]) >> e;

            this->AddWire(Wire<double>(index1, index2, r, e, windex));
            windex += 1;
        }
        return 0;
    }

    int ReadFromFile (const std::istream& sfile, identity<std::complex<double>>){
        std::stringstream ss;
        ss << sfile.rdbuf();
        std::string s = ss.str();
        s.push_back('\n');

        std::string point1("(\\d+)");
        std::string point2("(\\d+)");
        std::string resist("(-?\\d+(?:\\.\\d+)?\\s*R)");
        std::string capac("(-?\\d+(?:\\.\\d+)?\\s*C)");
        std::string ind("(-?\\d+(?:\\.\\d+)?\\s*L)");
        std::string opteds("(-?\\d+(?:\\.\\d+)?)\\s*V");
        std::string optphase("(-?\\d+(?:\\.\\d+)?)\\s*");

        std::regex word_regex(point1 + "\\s*--\\s*" + point2 + "\\s*,\\s*" + resist
            + "\\s*;\\s*" + capac + "\\s*;\\s*" + ind + "\\s*[;\\n]\\s*"
            + "(?:" +  opteds + "\\s*,\\s*" + optphase + "\\s*[;\\n])?");
        auto words_begin =
                std::sregex_iterator(s.begin(), s.end(), word_regex);
        auto words_end = std::sregex_iterator();

        if(words_begin == words_end){
            std::cerr << "Incorrect input file format." << std::endl;
            return -1;
        }

        int windex = 1;
        for(std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;

            int index1;
            int index2;
            double r;
            double l;
            double c;
            double e = 0;
            double fi = 0;
            std::istringstream (match[1]) >> index1;
            std::istringstream (match[2]) >> index2;
            std::istringstream (match[3]) >> r;
            std::istringstream (match[4]) >> l;
            std::istringstream (match[5]) >> c;

            if(match[6].str().length() != 0 || match[7].str().length() != 0){
                std::istringstream (match[6]) >> e;
                std::istringstream (match[7]) >> fi;
            }


            this->AddWire(Wire<std::complex<double>>(index1, index2, std::complex<double>(r, l-c),
                    std::complex<double>(e*cos(fi), -e*sin(fi)), windex));
            windex += 1;
        }
        return 0;
    }

public:
    int ReadFromFile (const std::istream& sfile){
        return ReadFromFile (sfile, identity<T>());
    }
};

#endif //CIRCUITS_CIRCUITACTIVE_H
