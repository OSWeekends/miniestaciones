export const useAuth = () => {
  const setUser = (payload: User, remember: boolean) => {
    if (remember) {
      // Save
      window.localStorage.setItem(AUTH_KEY, payload[AUTH_TOKEN]);
    }

    state.user = payload;
    state.error = undefined;
  };

  const logout = (): Promise<void> => {
    window.localStorage.removeItem(AUTH_KEY);
    return Promise.resolve((state.user = undefined));
  };

  return {
    setUser,
    logout,
    ...toRefs(state), // authenticating, user, error
  };
};
