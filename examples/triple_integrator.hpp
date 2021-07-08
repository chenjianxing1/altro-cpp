#pragma once

#include "altro/problem/dynamics.hpp"
#include "altro/eigentypes.hpp"

namespace altro {
namespace examples {

/**
 * @brief Triple integrator dynamics model, where the jerk is the control input
 *
 * State vector x = [x1 x2... v1 v2... a1 a2...]
 * Control vector u = [j1 j2...]
 * where xi, vi, ai, and ji are the position, velocity, acceration, and jerk in
 * dimension i.
 *
 */
class TripleIntegrator : public problem::ContinuousDynamics {
 public:
  TripleIntegrator(int dof = 1) : dof_(dof) {
    ALTRO_ASSERT(dof > 0, "The degrees of freedom must be greater than 0.");
  }

  int StateDimension() const override { return 3 * dof_; }
  int ControlDimension() const override { return dof_; }

  void EvaluateInplace(const VectorXdRef& x,
                       const VectorXdRef& u, const float t,
                       Eigen::Ref<VectorXd> xdot) const override;
  void Jacobian(const VectorXdRef& x,
                const VectorXdRef& u, const float t,
                Eigen::Ref<MatrixXd> jac) const override;
  void Hessian(const VectorXdRef& x,
               const VectorXdRef& u, const float t,
               const VectorXdRef& b,
               Eigen::Ref<MatrixXd> hess) const override;
  bool HasHessian() const override { return true; };

 private:
  int dof_;
};

}  // namespace examples
}  // namespace altro