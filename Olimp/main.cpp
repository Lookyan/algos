#include <iostream>

using namespace std;

class Heap
{
public:
    Heap(int n) : bufferSize(n), size(0) {
        buffer = new int[n];
    }
    ~Heap() {
        delete[] buffer;
    }
    void add(int num);
    int getMax();

private:
    void SiftUp(int i);
    void SiftDown(int i);
    
    int* buffer;
    int size;
    int bufferSize;
};

int main()
{
    /*
     * N - кол-во остановок 
     * M - кол-во мест в автобусе
    */
    int N = 0, M = 0;
    cin >> N >> M;
    
    Heap heap(M);
    
    int T = 0; //время проезда до следующей станции
    int K = 0; //кол-во работников
    int currentTime = 0; //время на текущей станции, если бы мы никогда не ждали
    
    for(int i = 0; i < N; i++) {
        cin >> T >> K;
        for(int j = 0; j < K; j++) {
            int time = 0;
            cin >> time;
            heap.add(time - currentTime);
        }
        currentTime += T;
    }
    
    cout << (currentTime + heap.getMax());
    
    return 0;
}

void Heap::add(int num)
{
    if(size < bufferSize) {
        buffer[size++] = num;
        SiftUp(size - 1);
    } else {
        if(num < buffer[0]) {
            buffer[0] = num;
            SiftDown(0);
        }
    }
}

void Heap::SiftUp(int i)
{
    while(i > 0) {
            int parent = (i - 1) / 2;
            if(buffer[i] <= buffer[parent])
                return;
            swap(buffer[i], buffer[parent]);
            i = parent;
    }
}

void Heap::SiftDown(int i)
{
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        if( left < size && buffer[left] > buffer[i] )
            largest = left;
        if( right < size && buffer[right] > buffer[largest] )
            largest = right;
        if( largest != i ) {
            std::swap(buffer[i], buffer[largest]);
            SiftDown(largest);
        }
}

int Heap::getMax()
{
    return buffer[0];
}
