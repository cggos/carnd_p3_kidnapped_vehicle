# Kidnapped Vehicle based on Particle Filter

* Udacity's Self-Driving Car Engineer Nanodegree Project 3: Kidnapped Vehicle

---

## Install & Build

```sh
sudo apt-get install libuv1-dev libssl-dev

# for Udacity's Self-Driving Car Simulator
git clone https://github.com/uWebSockets/uWebSockets 
cd uWebSockets
git checkout e94b6e1
mkdir build
cd build
cmake ..
make 
sudo make install
cd ..
cd ..
sudo ln -s /usr/lib64/libuWS.so /usr/lib/libuWS.so

# Download the Simulator
# ref: https://blog.csdn.net/u013468614/article/details/103608103
wget https://github.com/udacity/self-driving-car-sim/releases/download/v1.45/term2_sim_linux.zip
unzip term2_sim_linux.zip
cd term2_sim_linux
chmod +x term2_sim.x86_64

# the project
mkdir build
cd build
cmake ..
make -j `nproc`
```

## Run

* run **Udacity's Self-Driving Car Simulator**

  ```sh
  ./term2_sim.x86_64
  ```

  <p>
    <img src="imgs/term2_sim_linux_p3.png" />
    <img src="imgs/term2_sim_linux_p3_00.png" />
  </p>

* run the project
  ```sh
  # Run particle filter
  cd ./build
  ./particle_filter
  ```
* output
  ```
  Listening to port 4567
  Connected!!!
  highest w 7.14739e-05
  average w 5.1851e-05
  highest w 0.0165681
  average w 0.0104537
  highest w 0.00650401
  average w 0.00380714
  highest w 0.000215487
  average w 0.000110921
  ```

## Others

This is the particle filter project. If you want to know the localisation from scratch please visit my article in medium.

```
function(tol=0.2) {
    p = [0, 0, 0]
    dp = [1, 1, 1]
    best_error = move_robot()
    loop untill sum(dp) > tol
        loop until the length of p using i
            p[i] += dp[i]
            error = move_robot()

            if err < best_err
                best_err = err
                dp[i] *= 1.1
            else
                p[i] -= 2 * dp[i]
                error = move_robot()

                if err < best_err
                    best_err = err
                    dp[i] *= 1.1
                else
                    p[i] += dp[i]
                    dp[i] *= 0.9
    return p
}
```
