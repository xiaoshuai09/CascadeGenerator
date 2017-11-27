#ifndef SIMPLERNG_H
#define SIMPLERNG_H

// A simple random number generator based on George Marsaglia's MWC (Multiply With Carry) generator.
// This is not intended to take the place of the library's primary generator, Mersenne Twister.
// Its primary benefit is that it is simple to extract its state.

class SimpleRNG
{
public:
    
    SimpleRNG();

    // Seed the random number generator 
    void SetState(unsigned int u, unsigned int v);

    // Extract the internal state of the generator
    void GetState(unsigned int& u, unsigned int& v);

    // A uniform random sample from the open interval (0, 1) 
    float GetUniform();

    // A uniform random sample from the set of unsigned integers 
    unsigned int GetUint();

    // This stateless version makes it more convenient to get a uniform 
    // random value and transfer the state in and out in one operation.
    float GetUniform(unsigned int& u, unsigned int& v);

    // This stateless version makes it more convenient to get a random unsigned integer 
    // and transfer the state in and out in one operation.
    unsigned int GetUint(unsigned int& u, unsigned int& v);
        
    // Normal (Gaussian) random sample 
    float GetNormal(float mean, float standardDeviation);

    // Exponential random sample 
    float GetExponential(float mean);

	// Gamma random sample
    float GetGamma(float shape, float scale);

	// Chi-square sample
    float GetChiSquare(float degreesOfFreedom);

	// Inverse-gamma sample
    float GetInverseGamma(float shape, float scale);

	// Weibull sample
    float GetWeibull(float shape, float scale);

	// Cauchy sample
    float GetCauchy(float median, float scale);

	// Student-t sample
    float GetStudentT(float degreesOfFreedom);

    // The Laplace distribution is also known as the float exponential distribution.
    float GetLaplace(float mean, float scale);

	// Log-normal sample
    float GetLogNormal(float mu, float sigma);

	// Beta sample
    float GetBeta(float a, float b);

	// Poisson sample
	int GetPoisson(float lambda);

private:
    unsigned int m_u, m_v;
	int PoissonLarge(float lambda);
	int PoissonSmall(float lambda);
	float LogFactorial(int n);
};


#endif