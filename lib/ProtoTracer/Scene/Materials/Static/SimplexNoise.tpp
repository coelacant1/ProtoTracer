#pragma once

template<size_t colors>
SimplexNoise<colors>::SimplexNoise(int seed, GradientMaterial<colors>* gradientMaterial) {
    this->gradientMaterial = gradientMaterial;
    
    //the seed determines the swaps that occur between the default order and the order we're actually going to use
    for(int i = 0; i < 400; i++){
        uint8_t swapFrom = static_cast<uint8_t>(std::rand() % 256);
        uint8_t swapTo = static_cast<uint8_t>(std::rand() % 256);
        
        uint8_t temp = p[swapFrom];
        p[swapFrom] = p[swapTo];
        p[swapTo] = temp;
    }
    
    for(int i = 0; i < 512; i++){
        perm[i]=p[i & 255];
        permMod12[i] = perm[i] % 12;
    }
}

// 2D simplex noise
template<size_t colors>
float SimplexNoise<colors>::Noise(float xin, float yin) {
    float n0, n1, n2; // Noise contributions from the three corners
    
    // Skew the input space to determine which simplex cell we're in
    float s = (xin+yin)*F2; // Hairy factor for 2D
    int i = Mathematics::FFloor(xin+s);
    int j = Mathematics::FFloor(yin+s);
    float t = (i+j)*G2;
    float X0 = i-t; // Unskew the cell origin back to (x,y) space
    float Y0 = j-t;
    float x0 = xin-X0; // The x,y distances from the cell origin
    float y0 = yin-Y0;
    
    // For the 2D case, the simplex shape is an equilateral triangle.
    // Determine which simplex we are in.
    int i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords
    if(x0>y0) {i1=1; j1=0;} // lower triangle, XY order: (0,0)->(1,0)->(1,1)
    else {i1=0; j1=1;}      // upper triangle, YX order: (0,0)->(0,1)->(1,1)
    // A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
    // a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
    // c = (3-sqrt(3))/6
    
    float x1 = x0 - i1 + G2; // Offsets for middle corner in (x,y) unskewed coords
    float y1 = y0 - j1 + G2;
    float x2 = x0 - 1.0f + 2.0f * G2; // Offsets for last corner in (x,y) unskewed coords
    float y2 = y0 - 1.0f + 2.0f * G2;
    
    // Work out the hashed gradient indices of the three simplex corners
    int ii = i & 255;
    int jj = j & 255;
    int gi0 = permMod12[ii+perm[jj]];
    int gi1 = permMod12[ii+i1+perm[jj+j1]];
    int gi2 = permMod12[ii+1+perm[jj+1]];
    
    // Calculate the contribution from the three corners
    float t0 = 0.5f - x0*x0-y0*y0;
    if(t0 < 0) n0 = 0.0f;
    else {
        t0 *= t0;
        n0 = t0 * t0 * grad3[gi0].DotProduct(Vector3D(x0, y0, 0));//dot(grad3[gi0], x0, y0);  // (x,y) of grad3 used for 2D gradient
    }
    float t1 = 0.5f - x1*x1-y1*y1;
    if(t1 < 0) n1 = 0.0f;
    else {
        t1 *= t1;
        n1 = t1 * t1 * grad3[gi1].DotProduct(Vector3D(x1, y1, 0));//dot(grad3[gi1], x1, y1);
    }
    float t2 = 0.5f - x2*x2-y2*y2;
    if(t2 < 0) n2 = 0.0f;
    else {
        t2 *= t2;
        n2 = t2 * t2 * grad3[gi2].DotProduct(Vector3D(x2, y2, 0));//dot(grad3[gi2], x2, y2);
    }
    // Add contributions from each corner to get the final noise value.
    // The result is scaled to return values in the interval [-1,1].
    return 70.0f * (n0 + n1 + n2);
}

// 3D simplex noise
template<size_t colors>
float SimplexNoise<colors>::Noise(float xin, float yin, float zin) {
    float n0, n1, n2, n3; // Noise contributions from the four corners
    
    // Skew the input space to determine which simplex cell we're in
    float s = (xin+yin+zin)*F3; // Very nice and simple skew factor for 3D
    int i = Mathematics::FFloor(xin+s);
    int j = Mathematics::FFloor(yin+s);
    int k = Mathematics::FFloor(zin+s);
    float t = (i+j+k)*G3;
    float X0 = i-t; // Unskew the cell origin back to (x,y,z) space
    float Y0 = j-t;
    float Z0 = k-t;
    float x0 = xin-X0; // The x,y,z distances from the cell origin
    float y0 = yin-Y0;
    float z0 = zin-Z0;
    
    // For the 3D case, the simplex shape is a slightly irregular tetrahedron.
    // Determine which simplex we are in.
    int i1, j1, k1; // Offsets for second corner of simplex in (i,j,k) coords
    int i2, j2, k2; // Offsets for third corner of simplex in (i,j,k) coords
    
    if(x0>=y0) {
        if(y0>=z0) { i1=1; j1=0; k1=0; i2=1; j2=1; k2=0; } // X Y Z order
        else if(x0>=z0) { i1=1; j1=0; k1=0; i2=1; j2=0; k2=1; } // X Z Y order
        else { i1=0; j1=0; k1=1; i2=1; j2=0; k2=1; } // Z X Y order
    }
    else { // x0<y0
        if(y0<z0) { i1=0; j1=0; k1=1; i2=0; j2=1; k2=1; } // Z Y X order
        else if(x0<z0) { i1=0; j1=1; k1=0; i2=0; j2=1; k2=1; } // Y Z X order
        else { i1=0; j1=1; k1=0; i2=1; j2=1; k2=0; } // Y X Z order
    }
    
    // A step of (1,0,0) in (i,j,k) means a step of (1-c,-c,-c) in (x,y,z),
    // a step of (0,1,0) in (i,j,k) means a step of (-c,1-c,-c) in (x,y,z), and
    // a step of (0,0,1) in (i,j,k) means a step of (-c,-c,1-c) in (x,y,z), where
    // c = 1/6.
    float x1 = x0 - i1 + G3; // Offsets for second corner in (x,y,z) coords
    float y1 = y0 - j1 + G3;
    float z1 = z0 - k1 + G3;
    float x2 = x0 - i2 + 2.0f * G3; // Offsets for third corner in (x,y,z) coords
    float y2 = y0 - j2 + 2.0f * G3;
    float z2 = z0 - k2 + 2.0f * G3;
    float x3 = x0 - 1.0f + 3.0f * G3; // Offsets for last corner in (x,y,z) coords
    float y3 = y0 - 1.0f + 3.0f * G3;
    float z3 = z0 - 1.0f + 3.0f * G3;
    
    // Work out the hashed gradient indices of the four simplex corners
    int ii = i & 255;
    int jj = j & 255;
    int kk = k & 255;
    int gi0 = permMod12[ii+perm[jj+perm[kk]]];
    int gi1 = permMod12[ii+i1+perm[jj+j1+perm[kk+k1]]];
    int gi2 = permMod12[ii+i2+perm[jj+j2+perm[kk+k2]]];
    int gi3 = permMod12[ii+1+perm[jj+1+perm[kk+1]]];
    
    // Calculate the contribution from the four corners
    float t0 = 0.6f - x0*x0 - y0*y0 - z0*z0;
    if(t0 < 0) n0 = 0.0f;
    else {
        t0 *= t0;
        n0 = t0 * t0 * grad3[gi0].DotProduct(Vector3D(x0, y0, z0));//dot(grad3[gi0], x0, y0, z0);
    }
    
    float t1 = 0.6f - x1*x1 - y1*y1 - z1*z1;
    if(t1 < 0) n1 = 0.0f;
    else {
        t1 *= t1;
        n1 = t1 * t1 * grad3[gi1].DotProduct(Vector3D(x1, y1, z1));;//dot(grad3[gi1], x1, y1, z1);
    }
    
    float t2 = 0.6f - x2*x2 - y2*y2 - z2*z2;
    if(t2 < 0) n2 = 0.0f;
    else {
        t2 *= t2;
        n2 = t2 * t2 * grad3[gi2].DotProduct(Vector3D(x2, y2, z2));//dot(grad3[gi2], x2, y2, z2);
    }
    
    float t3 = 0.6f - x3*x3 - y3*y3 - z3*z3;
    if(t3 < 0) n3 = 0.0f;
    else {
        t3 *= t3;
        n3 = t3 * t3 * grad3[gi3].DotProduct(Vector3D(x3, y3, z3));//dot(grad3[gi3], x3, y3, z3);
    }
    
    // Add contributions from each corner to get the final noise value.
    // The result is scaled to stay just inside [-1,1]
    return 32.0f * (n0 + n1 + n2 + n3);
}

template<size_t colors>
void SimplexNoise<colors>::SetScale(Vector3D noiseScale){
    this->noiseScale = noiseScale;
}

template<size_t colors>
void SimplexNoise<colors>::SetZPosition(float zPosition){
    this->zPosition = zPosition;
}

template<size_t colors>
RGBColor SimplexNoise<colors>::GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) {
    position = position * noiseScale;

    float noise = Noise(position.X, position.Y, zPosition);
    
    return gradientMaterial->GetRGB(Vector3D(noise, 0, 0), Vector3D(), Vector3D());
}