#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * @brief
 * To track time limit
 */
#include <chrono>
auto start = chrono::steady_clock::now();
bool returnStatement(bool var)
{
    cout << "\n";
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "Used Time - 0," << chrono::duration<double, milli>(diff).count() << " s" << endl;

    return var;
}

//***************************************************

struct Request
{
    Request(int arrival_time, int process_time)
    {
        this->arrival_time = arrival_time;
        this->process_time = process_time;
    }

    int arrival_time;
    int process_time;
};

struct Response
{
    Response(bool dropped, int start_time)
    {
        this->dropped = dropped;
        this->start_time = start_time;
    }

    bool dropped;
    int start_time;
};

class Buffer
{
public:
    Buffer(int size) : size_(size),
                       finish_time_()
    {
    }

    Response Process(const Request &request)
    {

        while (!finish_time_.empty() && finish_time_.front() <= request.arrival_time)
            finish_time_.pop();

        if (finish_time_.empty())
        {
            finish_time_.push(request.arrival_time + request.process_time);
            return Response(false, request.arrival_time);
        }
        else
        {
            if (size_ > finish_time_.size())
            {
                int before = finish_time_.back();
                finish_time_.push(before + request.process_time);
                return Response(false, before);
            }

            return Response(true, 5);
        }
    }

private:
    int size_;
    queue<int> finish_time_;
};

void PrintResponses(const vector<Response> &responses)
{
    for (int i = 0; i < responses.size(); ++i)
        cout << (responses[i].dropped ? -1 : responses[i].start_time) << endl;
}

int main()
{
    int buffer_size;
    cin >> buffer_size;

    Buffer buffer(buffer_size);

    int count;
    cin >> count;

    vector<Request> requests;

    for (int i = 0; i < count; ++i)
    {
        int arrival_time, process_time;
        cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }

    vector<Response> responses;
    for (int i = 0; i < requests.size(); ++i)
    {
        responses.push_back(buffer.Process(requests[i]));
    }

    PrintResponses(responses);
    return 0;
}
