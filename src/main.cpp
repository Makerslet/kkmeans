
#include <iostream>
#include <vector>

#include <dlib/clustering.h>
#include <dlib/rand.h>
#include <dlib/string/string.h>


int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "error: number of clusters was not set, "
                     "please pass number of clusters as a numeric comand line argument" << std::endl;
        return 1;
    }

    int num_clusters = 1;
    std::string num_clusters_str(argv[1]);
    try {
        num_clusters = std::stoi(num_clusters_str);
    }
    catch(const std::invalid_argument& ex) {
        std::cout << "error: number of clusters " << ex.what() << std::endl;
        return 1;
    }
    catch(const std::out_of_range& ex) {
        std::cout << "error: number of clusters " << ex.what() << std::endl;
        return 1;
    }

    if(num_clusters < 0)
    {
        std::cout << "error: you can't use negative number, please use positive number" << std::endl;
        return 1;
    }

    using sample_type = dlib::matrix<double,2,1>;
    using kernel_type = dlib::radial_basis_kernel<sample_type>;

    std::vector<sample_type> samples;
    sample_type sample;

    std::string input_str;
    int line_number = 0;
    while(std::getline(std::cin, input_str))
    {
        std::vector<std::string> tokens = dlib::split(input_str, ";");

        if(tokens.size() != 2)
        {
            std::cout << "error: wrong data format in line " << line_number << std::endl;
            return 1;
        }

        int x,y;
        try {
            x = std::stoi(tokens[0]);
            y = std::stoi(tokens[1]);
        }
        catch(const std::invalid_argument& ex) {
            std::cout << "error: wrong data in line " << line_number << " " << ex.what() << std::endl;
            return 1;
        }
        catch(const std::out_of_range& ex) {
            std::cout << "error: wrong data in line " << line_number << " " << ex.what() << std::endl;
            return 1;
        }

        sample(0) = x;
        sample(1) = y;
        samples.push_back(sample);

        ++line_number;
    }

    dlib::kcentroid<kernel_type> kc(kernel_type(0.1),0.01, 8);
    dlib::kkmeans<kernel_type> test(kc);
    test.set_number_of_centers(num_clusters);

    std::vector<sample_type> initial_centers;
    pick_initial_centers(num_clusters, initial_centers, samples, test.get_kernel());
    test.train(samples, initial_centers);

    for (unsigned long i = 0; i < samples.size(); ++i)
    {
        std::cout << samples[i](0) << ";";
        std::cout << samples[i](1) << ";";
        std::cout << "cluster" << test(samples[i]) << std::endl;
    }

    return 0;
}
