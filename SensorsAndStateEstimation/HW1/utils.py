"""
File: utils.py
Project: HW1
File Created: Thursday, 11th April 2024 9:26:02 am
Author: Alfonso Toriz Vazquez (atoriz98@comunidad.unam.mx)
-----
Last Modified: Thursday, 9th May 2024 3:19:27 pm
Modified By: Alfonso Toriz Vazquez (atoriz98@comunidad.unam.mx>)
-----
License: MIT License
-----
Description: Useful functions for class.
"""

# Libraries
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns
from tqdm import tqdm


#  IO
class Io:
    @staticmethod
    def Mat2Pandas(mat: np.ndarray) -> pd.DataFrame:
        """Converts a Matlab mat file to a Pandas Dataframe.

        Parameters
        ----------
        mat : np.ndarray
            mat file loaded as numpy ndarray.

        Returns
        -------
        df : pd.Dataframe
            Pandas Dataframe with the mat file data.

        """
        # Get names
        colNames = [name for name in mat.dtype.names]

        # Crate dataframe
        df = pd.DataFrame()
        for name in colNames:
            df[name] = mat[name][0][0].squeeze()

        return df


# Visualization
class Visuals:
    @staticmethod
    def plotData(
        data: pd.DataFrame,
        x: str,
        columns: list[str],
        xlabel: str = None,
        ylabel: str = None,
        labels: list[str] = None,
        title: str = None,
        figsize: tuple[int, int] = (15, 5),
        **kwargs,
    ) -> None:
        """
        Fast and easy way of plotting multiple data that share the x-axis.

        Parameters
        ----------
        data : pd.DataFrame
            Data source.
        x : str
            x-axis (e.g. time)
        columns : list[str]
            Columns names to take data from for the y-axis. May be more than one.
        xlabel : str, optional
            x-axis label, by default None
        ylabel : str, optional
            y-axis label, by default None
        labels : list[str], optional
            Plot lengend labels, by default None
        title : str, optional
            Main figure title, by default None
        figsize : tuple[int, int], optional
            Matplotlib figure size, by default (15, 5)
        kwargs : Additional arguments for sns.lineplot.

        Raises
        ------
        KeyError
            x-axis column name not found in data source.
        KeyError
            y-axis column(s) name not found in data source.
        """
        # Check for x col
        if x not in data.columns:
            raise KeyError(f"{x} is not in data!")
        # Plot
        fig = plt.figure(figsize=figsize, layout="tight")
        for index, col in enumerate(columns):
            # Check for invalid column names
            if col not in data.columns:
                raise KeyError(f"Column '{col}' name not in data!")

            if labels is not None:
                sns.lineplot(
                    **kwargs, x=data[x], y=data[col], label=labels[index], legend=None
                )
            else:
                sns.lineplot(**kwargs, x=data[x], y=data[col])

        if xlabel is not None:
            plt.xlabel(xlabel)
        if ylabel is not None:
            plt.ylabel(ylabel)

        if title is not None:
            plt.title(title)

        plt.margins(x=0)

        for legob in fig.legend(bbox_to_anchor=(1, 1)).legend_handles:
            legob.set_linewidth(2.0)


# Math
class Math:
    @staticmethod
    def rotationMatrix2Euler(rotation_matrix: np.ndarray) -> np.ndarray:
        psi = np.arctan2(rotation_matrix[2, 1], rotation_matrix[2, 2])
        theta = np.arctan2(
            -rotation_matrix[2, 0],
            np.sqrt(rotation_matrix[2, 1] ** 2 + rotation_matrix[2, 2] ** 2),
        )
        phi = np.arctan2(rotation_matrix[1, 0], rotation_matrix[0, 0])

        return np.asarray([psi, theta, phi])

    @staticmethod
    def updateOrientation(
        previous_angular_vel: np.ndarray,
        delta: float,
        previous_rotation_matrix: np.ndarray = np.eye(3),
    ) -> np.ndarray:
        skew_matrix = np.array(
            [
                [0, -previous_angular_vel[2], previous_angular_vel[1]],
                [previous_angular_vel[2], 0, -previous_angular_vel[0]],
                [-previous_angular_vel[0], previous_angular_vel[1], 0],
            ]
        )
        current_rotation_matrix = previous_rotation_matrix @ (
            np.eye(3) + skew_matrix * delta
        )

        return current_rotation_matrix

    @staticmethod
    def updateVelocity(
        previous_acceleration: np.ndarray,
        delta: float,
        previous_velocity: np.ndarray = np.zeros(3),
    ) -> np.ndarray:
        return previous_velocity + previous_acceleration * delta

    @staticmethod
    def updatePosition(
        previous_velocity: np.ndarray,
        previous_acceleration: np.ndarray,
        delta: float,
        previous_position: np.ndarray = np.zeros(3),
    ) -> np.ndarray:
        return (
            previous_position
            + previous_velocity * delta
            + previous_acceleration * delta**2 / 2
        )

    @staticmethod
    def computePoseIntegrationMethod(
        data: pd.DataFrame,
        accel_cols: list[str],
        omg_cols: list[str],
        time_col: str,
        gravity_vector: np.ndarray,
    ) -> np.ndarray:
        # Initial variables
        previous_rotation_matrix = np.eye(3)
        previous_angular_vel = np.zeros(3)
        previous_acceleration = np.zeros(3)
        previous_velocity = np.zeros(3)
        previous_position = np.zeros(3)
        previous_time = 0.0

        results = np.zeros(
            (len(data), 9)  # (vx,vy,vz), (px, py, pz), (°x, °y, °z)
        )

        # Compute pose by simple integration
        for index, row in enumerate(
            tqdm(data[[time_col, *accel_cols, *omg_cols]].to_numpy())
        ):
            # First iter
            if index < 1:
                previous_time = row[0]
                previous_acceleration = row[1:4] - gravity_vector
                previous_angular_vel = row[4:]
                continue

            current_time = row[0]
            delta_time = current_time - previous_time

            current_acceleration = row[1:4] - gravity_vector
            current_angular_vel = row[4:]

            current_rotation_matrix = Math.updateOrientation(
                previous_angular_vel, delta_time, previous_rotation_matrix
            )

            current_velocity = Math.updateVelocity(
                previous_acceleration, delta_time, previous_velocity
            )

            current_position = Math.updatePosition(
                previous_velocity, previous_acceleration, delta_time, previous_position
            )

            # Save result
            results[index, :3] = Math.rotationMatrix2Euler(current_rotation_matrix)
            results[index, 3:6] = current_velocity
            results[index, 6:] = current_position

            # Update variables
            previous_time = current_time
            previous_acceleration = current_acceleration
            previous_angular_vel = current_angular_vel
            previous_rotation_matrix = current_rotation_matrix
            previous_velocity = current_velocity
            previous_position = current_position

        return results
