#include "sv/sorting/MergeSort.hpp"

namespace sv::sorting {

    void MergeSort::recordFrame(int h1, int h2) {
        m_frames.push_back({m_currentData, {h1, h2}, 0, 0}); // Liczniki nadpiszemy globalnymi
    }

    void MergeSort::merge(std::vector<int>& arr, int left, int mid, int right, int& comps, int& swaps) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<int> L(n1), R(n2);
        for (int i = 0; i < n1; i++) L[i] = arr[left + i];
        for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            comps++;
            recordFrame(left + i, mid + 1 + j);
            
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            swaps++; // Traktujemy przypisanie jako zamianę (swap) do celów statystyk
            m_currentData = arr;
            recordFrame(k, -1);
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            swaps++;
            m_currentData = arr;
            recordFrame(k, -1);
            i++; k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            swaps++;
            m_currentData = arr;
            recordFrame(k, -1);
            j++; k++;
        }
    }

    void MergeSort::mergeSortRecursive(std::vector<int>& arr, int left, int right, int& comps, int& swaps) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSortRecursive(arr, left, mid, comps, swaps);
        mergeSortRecursive(arr, mid + 1, right, comps, swaps);
        merge(arr, left, mid, right, comps, swaps);
    }

    void MergeSort::init(std::vector<int> data) {
        m_frames.clear();
        m_currentFrame = 0;
        m_finished = (data.size() <= 1);
        m_currentData = data;
        
        int totalComps = 0;
        int totalSwaps = 0;
        
        // Zapisz stan początkowy
        recordFrame(-1, -1);
        
        // Wykonaj pełne sortowanie w locie, nagrywając klatki
        std::vector<int> temp = data;
        mergeSortRecursive(temp, 0, temp.size() - 1, totalComps, totalSwaps);
        
        // Zaktualizuj liczniki we wszystkich klatkach (dla uproszczenia animacji)
        int currentC = 0, currentS = 0;
        for(auto& frame : m_frames) {
            frame.comps = currentC++;
            frame.swaps = currentS++;
            if(frame.comps > totalComps) frame.comps = totalComps;
            if(frame.swaps > totalSwaps) frame.swaps = totalSwaps;
        }
        
        // Zapisz stan końcowy
        m_frames.push_back({temp, {-1, -1}, totalComps, totalSwaps});
    }

    bool MergeSort::step() {
        if (m_finished || m_frames.empty()) return false;
        
        if (m_currentFrame < m_frames.size() - 1) {
            m_currentFrame++;
        } else {
            m_finished = true;
        }
        return !m_finished;
    }

    const std::vector<int>& MergeSort::getData() const {
        if(m_frames.empty()) return m_currentData;
        return m_frames[m_currentFrame].data;
    }
    
    std::pair<int, int> MergeSort::getHighlightedIndices() const { 
        if(m_frames.empty() || m_finished) return {-1, -1};
        return m_frames[m_currentFrame].highlighted;
    }
    
    int MergeSort::getComparisonsCount() const { return m_frames.empty() ? 0 : m_frames[m_currentFrame].comps; }
    int MergeSort::getSwapsCount() const { return m_frames.empty() ? 0 : m_frames[m_currentFrame].swaps; }
    std::string MergeSort::getName() const { return "Merge Sort"; }
    std::string MergeSort::getComplexityBest() const { return "O(n log n)"; }
    std::string MergeSort::getComplexityAverage() const { return "O(n log n)"; }
    std::string MergeSort::getComplexityWorst() const { return "O(n log n)"; }
    bool MergeSort::isFinished() const { return m_finished; }

}