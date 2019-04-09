#include "ouput_struct_of_pathlogies.h"
#include "pat_storage.h"
#include <algorithm>

list_of_output_pathlogies& create_list_of_pathlogies(unsigned int index_start_wave_copy, my_map& pathologies, list_of_output_pathlogies& list ){


    my_map::iterator iter_map = pathologies.begin();
    vector<unsigned int> indexes;

    if (iter_map != pathologies.end() && next(iter_map) != pathologies.end() && index_start_wave_copy > iter_map->first) {

        switch (iter_map->second)
        {
            case V_b:
                list.V_beat++;
                indexes.push_back(iter_map->first);
                break;
            case SV_b:
                list.SV_beat++;
                indexes.push_back(iter_map->first);
                break;
            case A_b:
                list.A_beat++;
                indexes.push_back(iter_map->first);
                break;
            case WPW:
                list.WPW++;
                indexes.push_back(iter_map->first);
                break;

            case VT:
                list.VT = true;
                indexes.push_back(iter_map->first);
                break;
            case SVTA:
                list.SVTA = true;
                indexes.push_back(iter_map->first);
                break;
            case AFIBR:
                list.AFIBR = true;
                indexes.push_back(iter_map->first);
                break;
            case AFl :
                list.Afl = true;
                indexes.push_back(iter_map->first);
                break;
            case BLOCKII:
                list.BlockII = true;
                indexes.push_back(iter_map->first);
                break;
            case SBR:
                list.SBR = true;
                indexes.push_back(iter_map->first);
                break;
            case VFIBR:
                list.VFl = true;
                indexes.push_back(iter_map->first);
                break;

            case V_T :
                list.V_T = true;
                indexes.push_back(iter_map->first);
                break;
            case V_B :
                list.V_B = true;
                indexes.push_back(iter_map->first);
                break;
            case SV_T :
                list.SV_T = true;
                indexes.push_back(iter_map->first);
                break;
            case SV_B:
                list.SV_B = true;
                indexes.push_back(iter_map->first);
                break;
            case A_T :
                list.A_T = true;
                indexes.push_back(iter_map->first);
                break;
            case A_B :
                list.A_B = true;
                indexes.push_back(iter_map->first);
                break;

        }

            pathologies.erase(pathologies.begin(), iter_map);
            list.data = new int(indexes.size());

            size_t i = 0;

            for (auto& i:indexes)
                *(list.data+i) = i;


    }

        return list;
}