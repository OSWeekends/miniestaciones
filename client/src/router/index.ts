import { createWebHistory, createRouter } from 'vue-router';

import { Auth } from '@/firebase.js';
// import About from '@/views/About';
import Home from '@/views/Home';

const routes = [
  { path: '/:pathMatch(.*)*', name: 'not-found', component: Home },
  {
    path: '/home',
    name: 'Home',
    component: () => import('@/views/Home.vue'),
  },
  {
    path: '/login',
    name: 'Login',
    component: () => import('@/views/Login.vue'),
  },
  {
    path: '/profile',
    name: 'Profile',
    component: () => import('@/views/Profile.vue'),
    meta: {
      requiresAuth: true,
    },
  },
  {
    path: '/dashboard',
    name: 'Dashboard',
    component: () => import('@/views/Dashboard.vue'),
    meta: {
      requiresAuth: true,
    },
  },
  {
    path: '/about',
    name: 'About',
    component: () => import('@/views/About.vue'),
    meta: {
      requiresAuth: true,
    },
  },
];

const router = createRouter({
  history: createWebHistory(),
  routes,
});

router.resolve({
  name: 'not-found',
  params: { pathMatch: ['not', 'found'] },
});

router.beforeEach((to, from, next) => {
  if (to.matched.some(route => route.meta.requiresAuth)) {
    if (!Auth.currentUser) {
      next({ name: 'Login' });
    } else {
      next();
    }
  } else {
    next();
  }
});
export default router;
